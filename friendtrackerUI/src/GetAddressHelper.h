/*
 * GetAddressHelper.h
 *
 *  Created on: 2013-03-29
 *      Author: Sukwon Oh
 */

#ifndef GETADDRESSHELPER_H_
#define GETADDRESSHELPER_H_

#include <QObject>
#include <QString>
#include <QtLocationSubset/QGeoServiceProvider>
#include <QtLocationSubset/QGeoSearchReply>

using namespace QtMobilitySubset;

class GetAddressHelper : public QObject
{
	Q_OBJECT

public:
	GetAddressHelper(QObject* containerObject, double lat, double lng, const QString& property);

public Q_SLOTS:
	void searchResults(QGeoSearchReply* reply);
	void searchError(QGeoSearchReply* reply, QGeoSearchReply::Error error, const QString& errorMessage);

private:
	QObject* m_containerObject;
	QString m_property;
};


#endif /* GETADDRESSHELPER_H_ */
