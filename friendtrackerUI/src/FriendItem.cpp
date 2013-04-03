/*
 * FriendList.cpp
 *
 *  Created on: 2013-03-30
 *      Author: Sukwon Oh
 */

#include "FriendItem.hpp"

#include "Utility.h"

#include <QStringList>
#include <QList>

#include <iostream>

using namespace std;

using namespace bb::platform::bbm;
using namespace bb::cascades;

FriendItem::FriendItem(QObject* parent, Contact& contact, ContactService* contactService, const QString& pin)
: QObject(parent)
, m_contact(contact)
, m_contactService(contactService)
, m_pin(pin)
{
	m_displayName = m_contact.displayName();

	// send image to main.qml when friend's display picture is updated
	bool connected = QObject::connect(m_contactService, SIGNAL(displayPictureUpdated(const QString &,
			const bb::platform::bbm::ImageType::Type, const QByteArray &)),
			this,
			SLOT(updateFriendDisplayPicture(const QString &,
			const bb::platform::bbm::ImageType::Type, const QByteArray &)));
	Q_ASSERT(connected);

	// detect a change on the user's contact
	connected = QObject::connect(m_contactService, SIGNAL(contactUpdated(const QString &)),
			this,
			SLOT(updateContact(const QString &)));
	Q_ASSERT(connected);
	Q_UNUSED(connected);

	// asynchronously populate displayPicture
	bool result = m_contactService->requestDisplayPicture(contact.handle());
	if (!result) {
		qWarning() << "FAILED TO GET FRIEND's PROFILE PICTURE";
	}

	m_userStatus = m_contact.status();
	m_statusMessage = m_contact.statusMessage();
	m_personalMessage = m_contact.personalMessage();
	m_ppId = m_contact.ppId();
	m_handle = m_contact.handle();
}

void FriendItem::updateContact(const QString& contactHandle)
{
	const Contact contact = m_contactService->contact(contactHandle);
	// if not a empty Contact
	if (contact.displayName() != "") {
		if (m_userStatus != contact.status()) {
			m_userStatus = contact.status();
			emit userStatusChanged(m_userStatus);
		}
		if (m_statusMessage != contact.statusMessage()) {
			m_statusMessage = contact.statusMessage();
			emit statusMessageChanged(m_statusMessage);
		}
		if (m_personalMessage != contact.personalMessage()) {
			m_personalMessage = contact.personalMessage();
			emit personalMessageChanged(m_personalMessage);
		}
	}
}

QString FriendItem::displayName() const
{
	return m_displayName;
}

Image FriendItem::profilePicture() const
{
	return m_profilePicture;
}

UserStatus::Type FriendItem::userStatus() const
{
	return m_userStatus;
}

QString FriendItem::statusMessage() const
{
	return m_statusMessage;
}

QString FriendItem::personalMessage() const
{
	return m_personalMessage;
}

QString FriendItem::ppId() const
{
	return m_ppId;
}

QString FriendItem::pin() const
{
	return m_pin;
}

/*
 * A Friend's Profile Picture is asynchronously returned here.
 * Notify main.qml to dynamically update the friend's pin image.
 */
void FriendItem::updateFriendDisplayPicture(const QString& handle,
												 const bb::platform::bbm::ImageType::Type imageType,
												 const QByteArray& displayPicture)
{
	Q_UNUSED(imageType);
	if (m_handle == handle) {
		m_profilePicture = Utility::scaleImage(displayPicture, 140, 140);
		emit profilePictureChanged(m_profilePicture);
	}
}
