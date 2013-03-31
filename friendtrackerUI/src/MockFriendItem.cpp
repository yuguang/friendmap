/*
 * MockFriendItem.cpp
 *
 *  Created on: 2013-03-30
 *      Author: soh
 */

#include "MockFriendItem.hpp"

#include "Utility.h"

using namespace bb::platform::bbm;
using namespace bb::cascades;

#include <iostream>
using namespace std;

MockFriendItem::MockFriendItem(QObject* parent,
		const QString& displayName,
		bb::platform::bbm::UserStatus::Type status,
		const QString& statusMessage,
		const QString& personalMessage)
: QObject(parent)
, m_displayName(displayName)
, m_userStatus(status)
, m_statusMessage(statusMessage)
, m_personalMessage(personalMessage)
, m_ppId(displayName)
, m_pin("testpin")
{
	QFile defaultImage("app/native/assets/images/default.jpg");
    if (!defaultImage.open(QIODevice::ReadOnly))
        return;

    const QByteArray imageData = defaultImage.readAll();
    m_profilePicture = Utility::scaleImage(imageData, 400, 400);
}

QString MockFriendItem::displayName() const
{
	return m_displayName;
}

Image MockFriendItem::profilePicture() const
{
	return m_profilePicture;
}

UserStatus::Type MockFriendItem::userStatus() const
{
	return m_userStatus;
}

QString MockFriendItem::statusMessage() const
{
	return m_statusMessage;
}

QString MockFriendItem::personalMessage() const
{
	return m_personalMessage;
}

QString MockFriendItem::ppId() const
{
	return m_ppId;
}

QString MockFriendItem::pin() const
{
	return m_pin;
}
