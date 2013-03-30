/*
 * Utility.h
 *
 *  Created on: 2013-03-29
 *      Author: soh
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <QByteArray>

namespace QtMobilitySubset {
	class QGeoSearchManager;
}

class Utility
{
public:
	static QByteArray scaleImage(const QByteArray& imageDdata, int width, int height);
	static QtMobilitySubset::QGeoSearchManager* getSearchManager();
};


#endif /* UTILITY_H_ */
