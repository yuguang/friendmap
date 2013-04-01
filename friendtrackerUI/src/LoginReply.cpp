/*
 * LoginReply.cpp
 *
 *  Created on: 2013-03-16
 *      Author: soh
 */

#include <bb/data/JsonDataAccess>
#include <QVariant>
#include <iostream>

#include "LoginReply.h"

using namespace std;
using namespace bb::data;

LoginReply::LoginReply()
: m_status(false)
{}

bool LoginReply::parse(const QByteArray& data)
{
	JsonDataAccess jsonObject;
	QVariant node = jsonObject.loadFromBuffer(data);
	if (jsonObject.hasError()) {
		cout << "error converting JSON data: " << jsonObject.error().errorMessage().toStdString() << endl;
	} else {
		cout << "before parse: " << QString(data).toStdString() << endl;
		QVariantMap map = node.value<QVariantMap>();
		if (map["status"].toString() == "OK") {
			m_status = true;
			m_sessionKey = map["sessionKey"].toString();
			QVariantList friendList = map["friends"].value<QVariantList>();
			for (int i = 0; i < friendList.size(); i++) {
				m_ppIds.append(friendList[i].toString());
			}
			QVariantList pinList = map["pins"].value<QVariantList>();
			for (int i = 0; i < pinList.size(); i++) {
				m_pins.append(pinList[i].toString());
			}

			return true;
		}
	}

	return false;
}

QString LoginReply::getType() const
{
	static QString type("login");
	return type;
}

QString LoginReply::getSessionKey() const
{
	return m_sessionKey;
}

QStringList LoginReply::getFriends() const
{
	return m_ppIds;
}

QStringList LoginReply::getPins() const
{
	return m_pins;
}
