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

class ServerInterface : public QObject
{
	Q_OBJECT

public:
	ServerInterface(QObject* parent = 0);

	void sendMessage(const Message& msg) const;
	void receiveMessage() const;

signals:
	void loginSuccess(const QString& sessionKey);

public slots:
	void parseReply(QNetworkReply* );

private:
	Reply* buildReply(const QByteArray &);
	QNetworkAccessManager* m_NetworkAccessManager;
};


#endif /* SERVERINTERFACE_H_ */
