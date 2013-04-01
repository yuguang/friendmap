/*
 * UpdateLocationMessage.cpp
 *
 *  Created on: 2013-03-16
 *      Author: Sukwon Oh
 */

#include "UpdateLocationMessage.h"
#include <sstream>

using namespace std;

QUrl UpdateLocationMessage::url = QUrl("http://friendtracker.org:9000/update");

UpdateLocationMessage::UpdateLocationMessage(const QString& ppId,
											 double lat,
											 double lon,
											 int visibility,
											 const QString& sessionKey)
: m_ppId(ppId), latitude(lat), longitude(lon), m_visibility(visibility), m_sessionKey(sessionKey)
{}

QByteArray UpdateLocationMessage::serialize() const
{
	stringstream jsonStream;
	jsonStream << "{\"ppId\":\"" << m_ppId.toStdString()
			   << "\",\"x\":" << latitude
			   << ",\"y\":" << longitude
			   << ",\"v\":" << m_visibility
			   << ",\"sessionKey\":\"" << m_sessionKey.toStdString()
			   << "\"}";

	return jsonStream.str().c_str();
}

QUrl UpdateLocationMessage::getUrl() const
{
	return url;
}
