/*
 * UpdateLocationMessage.h
 *
 *  Created on: 2013-03-16
 *      Author: Sukwon Oh
 */

#ifndef UPDATELOCATIONMESSAGE_H_
#define UPDATELOCATIONMESSAGE_H_

#include "Message.h"
#include <QString>
#include <QByteArray>
#include <QUrl>

class UpdateLocationMessage : public Message
{
	QString m_ppId;
	double latitude;
	double longitude;
	QString m_sessionKey;
	int m_visibility;

	static QUrl url;

public:
	UpdateLocationMessage(const QString& ppId, double lat, double lon, int visibility, const QString& sessionKey);

	QByteArray serialize() const;
	QUrl getUrl() const;
};


#endif /* UPDATELOCATIONMESSAGE_H_ */
