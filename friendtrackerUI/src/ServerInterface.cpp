/*
 * ServerInterface.cpp
 *
 *  Created on: 2013-03-16
 *      Author: soh
 */

#include "ServerInterface.h"
#include <sstream>
#include <QNetworkRequest>
#include <bb/data/JsonDataAccess>
#include <iostream>

#include "LoginReply.h"
#include "UpdateLocationReply.h"

using namespace std;
using namespace bb::data;

ServerInterface::ServerInterface(QObject* parent)
: QObject(parent)
, m_NetworkAccessManager(new QNetworkAccessManager(parent))
{
	bool connected = connect(m_NetworkAccessManager,
			SIGNAL(finished(QNetworkReply* )),
			this,
			SLOT(parseReply(QNetworkReply* )));

	Q_ASSERT(connected);
	Q_UNUSED(connected);
}

void ServerInterface::sendMessage(const Message& msg) const
{
	QNetworkRequest request(msg.getUrl());
	request.setRawHeader("Content-Type", "application/json");

	const QByteArray& byteMsg = msg.serialize();
	cout << "sending msg: " << QString(byteMsg).toStdString() << endl;

	m_NetworkAccessManager->post(request, byteMsg);
}

void ServerInterface::receiveMessage() const
{

}

Reply* ServerInterface::buildReply(const QByteArray& data)
{
	JsonDataAccess jsonObject;
	QVariant node = jsonObject.loadFromBuffer(data);
	if (jsonObject.hasError()) {
		return 0;
	} else {
		QVariantMap map = node.value<QVariantMap>();
		if (map["type"].toString() == "login") {
			return new LoginReply();
		} else if (map["type"].toString() == "update") {
			return new UpdateLocationReply();
		} else {
			return 0;
		}
	}
}

void ServerInterface::parseReply(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError) {
		QByteArray bytes = reply->readAll();
		cout << QString(bytes).toStdString() << endl;
		Reply* reply = buildReply(bytes);
		if (reply) {
			bool result = reply->parse(bytes);
			if (result) {
				if (reply->getType() == "login") {
					emit onSessionKeyChanged(dynamic_cast<LoginReply *>(reply)->getSessionKey());
					emit onFriendListChanged(dynamic_cast<LoginReply *>(reply)->getFriends());
				}
			}
			Q_UNUSED(result);
		} else {
			cout << "parse error" << endl;
		}
	} else {
		cout << "error!: " << reply->error() << endl;
	}
}
