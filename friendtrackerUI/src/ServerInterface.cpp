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
#include <bb/system/SystemToast>

#include <iostream>

#include "LoginReply.h"
#include "UpdateLocationReply.h"
#include "GetLocationsReply.h"

using namespace std;
using namespace bb::data;
using namespace bb::system;

ServerInterface::ServerInterface(QObject* parent)
: QObject(parent)
, m_NetworkAccessManager(new QNetworkAccessManager(parent))
, m_isLoggedIn(false)
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
		} else if (map["type"].toString() == "location") {
			return new GetLocationsReply();
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
					emit onPinListChanged(dynamic_cast<LoginReply *>(reply)->getPins());
					m_isLoggedIn = true;
				} else if (reply->getType() == "location") {
					emit onGetLocations(dynamic_cast<GetLocationsReply *>(reply)->getFriends());
				}
			} else {
				if (reply->getType() == "login") {
					SystemToast toast;
					toast.setBody("Oops, Login Failed!");
					toast.exec();
					// kill application here
					emit loginFailed();
				}
			}
			Q_UNUSED(result);
		} else {
			cout << "parse error" << endl;
		}
	} else {
		SystemToast toast;
		toast.setBody(reply->errorString());
		toast.exec();
		if (!m_isLoggedIn) {
			// kill application here
			emit loginFailed();
		}
	}
}
