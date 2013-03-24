/*
 * LoginMessage.cpp
 *
 *  Created on: 2013-03-16
 *      Author: soh
 */

#include "LoginMessage.h"
#include <sstream>

using namespace std;

QUrl LoginMessage::url = QUrl("http://friendtracker.org:9000/login");

LoginMessage::LoginMessage(const QString& ppId,
						   double lat,
						   double lon)
: m_ppId(ppId), latitude(lat), longitude(lon)
{}

LoginMessage::LoginMessage(const QString& ppId,
						   double lat,
						   double lon,
						   const QStringList& friends)
: m_ppId(ppId), latitude(lat), longitude(lon), friends(friends)
{}

QByteArray LoginMessage::serialize() const
{
	stringstream jsonStream;
	jsonStream << "{\"ppId\":\"" << m_ppId.toStdString()
			   << "\",\"x\":" << latitude
			   << ",\"y\":" << longitude
			   << ",\"friends\":[";

	for (unsigned int i = 0; i < friends.size(); i++) {
		if (i > 0) jsonStream << ",";
		jsonStream << "\"" << friends.at(i).toStdString() << "\"";
	}

	jsonStream << "]}";

	return jsonStream.str().c_str();
}

QUrl LoginMessage::getUrl() const
{
	return url;
}
