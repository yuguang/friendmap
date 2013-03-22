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
#include <vector>

class LoginMessage : public Message
{
	QString m_ppId;
	double latitude;
	double longitude;
	std::vector<QString> friends;

	static QUrl url;

public:
	LoginMessage(const QString& ppId, double lat, double lon);
	LoginMessage(const QString& ppId, double lat, double lon, const std::vector<QString>& friends);

	QByteArray serialize() const;
	QUrl getUrl() const;
};


#endif /* LOGINMESSAGE_H_ */
