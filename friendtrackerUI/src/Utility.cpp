/*
 * Utility.cpp
 *
 *  Created on: 2013-03-29
 *      Author: soh
 */

#include "Utility.h"
#include "Exceptions.h"
#include <QObject>
#include <QByteArray>
#include <bb/cascades/Image>
#include <bb/ImageData>
#include <bb/utility/ImageConverter>

#include <QtLocationSubset/QGeoServiceProvider>

using namespace QtMobilitySubset;

QByteArray Utility::scaleImage(const QByteArray& imageData, int width, int height)
{
	QImage scaledImage;
	if (!scaledImage.loadFromData(imageData)) {
		throw ScaleImageException();
	} else {
		scaledImage = scaledImage.scaled(width, height, Qt::KeepAspectRatio);
	}
	const QImage swappedImage = scaledImage.rgbSwapped();
	bb::ImageData imageData2 = bb::ImageData::fromPixels(swappedImage.bits(),
	bb::PixelFormat::RGBX, swappedImage.width(), swappedImage.height(), swappedImage.bytesPerLine());
	return bb::utility::ImageConverter::encode("image/jpeg", imageData2);
}

QGeoSearchManager* Utility::getSearchManager()
{
	static QGeoServiceProvider serviceProvider("BbGeoServices");
	return serviceProvider.searchManager();
}
