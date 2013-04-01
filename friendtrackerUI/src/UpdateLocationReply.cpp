/*
 * UpdateLocationReply.cpp
 *
 *  Created on: 2013-03-16
 *      Author: soh
 */

#include "UpdateLocationReply.h"
#include <bb/data/JsonDataAccess>
#include <QVariant>
#include <iostream>

using namespace bb::data;
using namespace std;

bool UpdateLocationReply::parse(const QByteArray& data)
{
	JsonDataAccess jsonObject;
	QVariant node = jsonObject.loadFromBuffer(data);
	if (jsonObject.hasError()) {
		cout << "error converting JSON data: " << jsonObject.error().errorMessage().toStdString() << endl;
	} else {
		cout << "before parse: " << QString(data).toStdString() << endl;
		QVariantMap map = node.value<QVariantMap>();
		if (map["status"].toString() == "OK") {
			return true;
		}
	}

	return false;
}

QString UpdateLocationReply::getType() const
{
	static QString type("update");
	return type;
}
