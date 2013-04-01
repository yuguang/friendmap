/*
 * GetAddressHelper.cpp
 *
 *  Created on: 2013-03-29
 *      Author: soh
 */


#include "GetAddressHelper.h"
#include <QByteArray>
#include <QtLocationSubset/QGeoServiceProvider>
#include <QtLocationSubset/QGeoSearchManager>
#include <bb/cascades/Container>

#include "Utility.h"

#include <iostream>
#include <sstream>
using namespace std;
using namespace QtMobilitySubset;
using namespace bb::cascades;

GetAddressHelper::GetAddressHelper(QObject* containerObject, double lat, double lng)
: m_containerObject(containerObject)
{
	QGeoSearchManager* searchManager = Utility::getSearchManager();
	QGeoSearchReply* reply = searchManager->reverseGeocode(QGeoCoordinate(lat, lng));
	if (reply->isFinished()) {
		if (reply->error() == QGeoSearchReply::NoError) {
			searchResults(reply);
		} else {
			searchError(reply, reply->error(), reply->errorString());
		}
	}

    bool result = connect(searchManager,
            SIGNAL(finished(QGeoSearchReply *)),
            this,
            SLOT(searchResults(QGeoSearchReply *)));
    Q_ASSERT(result);

    result = connect(searchManager,
            SIGNAL(error(QGeoSearchReply *, QGeoSearchReply::Error , QString)),
            this,
            SLOT(searchError(QGeoSearchReply *, QGeoSearchReply::Error, QString)));
    Q_ASSERT(result);
    Q_UNUSED(result);
}

void GetAddressHelper::searchResults(QGeoSearchReply* reply)
{
	QList<QGeoPlace> places = reply->places();
	Container* container = qobject_cast<Container*>(m_containerObject);
	container->setProperty("bubbleText", places.at(0).address().text());

	// disconnect all signals to the search manager
	Utility::getSearchManager()->disconnect();

	reply->deleteLater();
}
void GetAddressHelper::searchError(QGeoSearchReply* reply, QGeoSearchReply::Error error,
		const QString& errorMessage)
{
	cout << "SEARCH ERROR: " << errorMessage.toStdString() << endl;
	// disconnect all signals to the search manager
	Utility::getSearchManager()->disconnect();
	reply->deleteLater();
}
