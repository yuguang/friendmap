/*
 * GetLocationMessage.cpp
 *
 *  Created on: 2013-03-25
 *      Author: Sukwon Oh
 */

#include "GetLocationsMessage.h"
#include <sstream>

using namespace std;

QUrl GetLocationsMessage::url = QUrl("http://friendtracker.org:8081/getLocations");

GetLocationsMessage::GetLocationsMessage(const QStringList& ppIds)
:m_ppIds(ppIds)
{}

QByteArray GetLocationsMessage::serialize() const {
	stringstream jsonStream;

	jsonStream << "{\"friends\": [";
	for (int i = 0; i < m_ppIds.size(); i++) {
		if (i > 0) jsonStream << ",";
		jsonStream << "\"" << m_ppIds.at(i).toStdString() << "\"";
	}

	jsonStream << "]}";

	return jsonStream.str().c_str();
}

QUrl GetLocationsMessage::getUrl() const {
	return url;
}
