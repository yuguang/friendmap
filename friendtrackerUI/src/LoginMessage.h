/*
 * LoginMessage.h
 *
 *  Created on: 2013-03-16
 *      Author: soh
 */

#ifndef LOGINMESSAGE_H_
#define LOGINMESSAGE_H_

#include "Message.h"
#include <QString>
#include <QStringList>

class LoginMessage : public Message
{
	QString m_ppId;
	double latitude;
	double longitude;
	QStringList friends;

	static QUrl url;

public:
	LoginMessage(const QString& ppId, double lat, double lon);
	LoginMessage(const QString& ppId, double lat, double lon, const QStringList& friends);

	QByteArray serialize() const;
	QUrl getUrl() const;
};


#endif /* LOGINMESSAGE_H_ */
