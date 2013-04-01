/*
 * GetLocationsReply.cpp
 *
 *  Created on: 2013-03-25
 *      Author: soh
 */

#include <bb/data/JsonDataAccess>
#include <QVariant>
#include <iostream>

#include "GetLocationsReply.h"

using namespace std;
using namespace bb::data;

GetLocationsReply::GetLocationsReply()
: m_status(false)
{}

bool GetLocationsReply::parse(const QByteArray& data)
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
			QVariantList friendList = map["friends"].value<QVariantList>();
			for (int i = 0; i < friendList.size(); i++) {
				QString friendStr = friendList[i].toString();
				QStringList fields = friendStr.split(",");
				// if incorrect number of fields, stop parsing
				if (fields.size() != 4) return false;
				QString ppId = fields.at(0);
				double x = fields.at(1).toDouble();
				double y = fields.at(2).toDouble();
				int visibility = fields.at(3).toInt();
				m_friends.append(User(ppId, x, y, visibility));
			}

			return true;
		}
	}

	return false;
}

QString GetLocationsReply::getType() const
{
	static QString type("location");
	return type;
}

QList<User> GetLocationsReply::getFriends() const
{
	return m_friends;
}


