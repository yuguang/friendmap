/*
 * GetLocation.h
 *
 *  Created on: 2013-03-25
 *      Author: Sukwon Oh
 */

#ifndef GETLOCATION_H_
#define GETLOCATION_H_

#include "Message.h"
#include <QString>
#include <QStringList>

class GetLocationsMessage : public Message
{
	QStringList m_ppIds;

	static QUrl url;

public:
	GetLocationsMessage(const QStringList& ppId);

	QByteArray serialize() const;
	QUrl getUrl() const;
};


#endif /* GETLOCATION_H_ */
