/*
 * FriendList.cpp
 *
 *  Created on: 2013-03-30
 *      Author: soh
 */

#include "FriendItem.hpp"

#include "Utility.h"

#include <QStringList>
#include <QList>

#include <iostream>

using namespace std;

using namespace bb::platform::bbm;
using namespace bb::cascades;

FriendItem::FriendItem(QObject* parent, Contact& contact, ContactService* contactService)
: QObject(parent)
, m_contact(contact)
, m_contactService(contactService)
{
	m_displayName = m_contact.displayName();

	// send image to main.qml when friend's display picture is updated
	bool connected = QObject::connect(m_contactService, SIGNAL(displayPictureUpdated(const QString &,
			const bb::platform::bbm::ImageType::Type, const QByteArray &)),
			this,
			SLOT(updateFriendDisplayPicture(const QString &,
			const bb::platform::bbm::ImageType::Type, const QByteArray &)));
	Q_ASSERT(connected);
	Q_UNUSED(connected);

	// asynchronously populate displayPicture
	bool result = m_contactService->requestDisplayPicture(contact.handle());
	if (!result) {
		cout << "FAILED TO GET FRIEND's PROFILE PICTURE" << endl;
	}

	m_userStatus = m_contact.status();
	m_statusMessage = m_contact.statusMessage();
	m_personalMessage = m_contact.personalMessage();
	m_ppId = m_contact.ppId();
}

QString FriendItem::displayName() const
{
	return m_displayName;
}

Image FriendItem::profilePicture() const
{
	// asynchronously populate displayPicture
	bool result = m_contactService->requestDisplayPicture(m_contact.handle());
	if (!result) {
		cout << "FAILED TO GET FRIEND's PROFILE PICTURE" << endl;
	}
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

/*
 * A Friend's Profile Picture is asynchronously returned here.
 * Notify main.qml to dynamically update the friend's pin image.
 */
void FriendItem::updateFriendDisplayPicture(const QString& handle,
												 const bb::platform::bbm::ImageType::Type imageType,
												 const QByteArray& displayPicture)
{
	Q_UNUSED(imageType);
	m_profilePicture = Utility::scaleImage(displayPicture, 140, 140);
}
