/*
 * ServerInterface.h
 *
 *  Created on: 2013-03-16
 *      Author: soh
 */

#ifndef SERVERINTERFACE_H_
#define SERVERINTERFACE_H_

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include "Message.h"
#include "Reply.h"
#include <QStringList>
#include <QList>

#include "GetLocationsReply.h"

class ServerInterface : public QObject
{
	Q_OBJECT

public:
	ServerInterface(QObject* parent = 0);

	void sendMessage(const Message& msg) const;
	void receiveMessage() const;

signals:
	void onSessionKeyChanged(const QString& sessionKey);
	void onFriendListChanged(const QStringList &);
	void onGetLocations(const QList<User> &);
	void loginSuccess();
	void loginFailed();

public slots:
	void parseReply(QNetworkReply* );

private:
	Reply* buildReply(const QByteArray &);
	QNetworkAccessManager* m_NetworkAccessManager;
	bool m_isLoggedIn;
};


#endif /* SERVERINTERFACE_H_ */
