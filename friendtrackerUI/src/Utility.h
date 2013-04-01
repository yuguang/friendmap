/*
 * Utility.h
 *
 *  Created on: 2013-03-29
 *      Author: Sukwon Oh
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <QByteArray>
#include <QString>

namespace QtMobilitySubset {
	class QGeoSearchManager;
}

class Utility
{
public:
	static QByteArray scaleImage(const QByteArray& imageDdata, int width, int height);
	static QtMobilitySubset::QGeoSearchManager* getSearchManager();
	static void showToast(const QString &);
	static void execToast(const QString &);
};


#endif /* UTILITY_H_ */
