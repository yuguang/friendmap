/**
 * MapView for the Frientracker App
 *
 * by Sukwon Oh
 */
#ifndef WEBMAPS_HPP
#define WEBMAPS_HPP

#include <QObject>
#include <QMap>
#include <QVariant>
#include <bb/system/SystemProgressDialog.hpp>
#include <QtLocationSubset/QGeoPositionInfo>
#include <QtLocationSubset/QGeoPositionInfoSource>
#include <QtLocationSubset/QGeoCoordinate>

using namespace QtMobilitySubset;

namespace bb{
	namespace system {
		class InvokeTargetReply;
	}
}

//! [0]
class WebMaps : public QObject
{
    Q_OBJECT

    // The current location (latitude) used by main.qml
    Q_PROPERTY(double myLat READ getMyLatitude NOTIFY myLatChanged)

    // The current location (longitude) used by main.qml
    Q_PROPERTY(double myLon READ getMyLongitude NOTIFY myLonChanged)

public:
    WebMaps(QObject *parent = 0);

    void init();
    double getMyLatitude() const;
    double getMyLongitude() const;
    void setRegularMode();
    void setRealtimeMode();
    void updateFriendLocation(const QString &, double, double, int);
    void startChat(QObject* parent, const QString& pin);

    Q_INVOKABLE void setGeoLocationInterval(float value);
    Q_INVOKABLE QVariantList worldToPixelInvokable(QObject* mapObject, double lat, double lon) const;
    Q_INVOKABLE void updateMarkers(QObject* mapObject, QObject* containerObject) const;
    Q_INVOKABLE void addPin(const QString& ppId, QObject* object);
    Q_INVOKABLE QObject* getPin(const QString& ppId) const;

public slots:
    void positionUpdateTimeout();
    void positionUpdatedHandler(const QGeoPositionInfo& info);

    void onInvokeResult();

signals:
    // The change notification signals of the properties
    void myLatChanged(double x);
    void myLonChanged(double y);
    void getCurrentLocationFailed();	// exit app on this signal
    void gotMyLocation(const QGeoCoordinate& coord);
    void myLocationChanged(const QGeoCoordinate& coord);
    void subscribe();
    void unsubscribe();
    void friendLocationChanged(const QString& ppId, double x, double y, int visibility);

private:
    QPoint worldToPixel(QObject* mapObject, double latitude, double longitude) const;

    QGeoPositionInfoSource* m_positionInfoSource;
    QGeoCoordinate myLocation;
    bool initialized;
    bb::system::InvokeTargetReply* m_invokeTargetReply;
    QMap<QString, QObject *> m_pinMap;
};
//! [0]

#endif
