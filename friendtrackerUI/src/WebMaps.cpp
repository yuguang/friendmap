/**
 * Friendtracker UI
 *
 * This is a mediator class managing many different parts of the Friendtracker App.
 * Written By: Sukwon Oh, Bill Chen
 */
#include "WebMaps.hpp"
#include "FriendtrackerUI.hpp"

#include <QDebug>
#include <QFile>
#include <QTimer>

#include <bb/location/PositionErrorCode>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeTarget>
#include <bb/system/InvokeTargetReply>
#include <bb/system/SystemToast>
#include <bb/system/CardDoneMessage>

#include <bb/cascades/Container>
#include <bb/cascades/maps/MapView>
#include <bb/platform/geo/Point.hpp>
#include <QPoint>

#include <iostream>
#include <sstream>

#include "Exceptions.h"
#include "Utility.h"

using namespace bb::cascades;
using namespace bb::cascades::maps;
using namespace bb::platform::geo;
using namespace bb::system;
using namespace QtMobilitySubset;
using namespace std;

//! [0]
WebMaps::WebMaps(QObject *parent)
    : QObject(parent)
	, m_positionInfoSource(QGeoPositionInfoSource::createDefaultSource(parent))
	, initialized(false)
{
	// Start getting current location
	if (m_positionInfoSource == 0) {
		SystemToast toast;
		toast.setBody("Failed to get current location! Exiting...");
		toast.exec();
		throw InitializationException("Failed to get current location");
	}

	// applied previously saved update frequency settings
	FriendtrackerUI* friendtracker = (FriendtrackerUI *) parent;
	m_positionInfoSource->setUpdateInterval((int)friendtracker->getValueFor("updateFrequencySlider", "5").toDouble() * 1000);
	m_positionInfoSource->setProperty("accuracy", 2.0);	// set accuracy within 2m
}

void WebMaps::init()
{
	bool updateTimeoutConnected = connect(m_positionInfoSource,
			SIGNAL(updateTimeout()),
	    	this,
	    	SLOT(positionUpdateTimeout()));
	Q_ASSERT(updateTimeoutConnected);
	Q_UNUSED(updateTimeoutConnected);

	bool positionUpdatedConnected = connect(m_positionInfoSource,
			SIGNAL(positionUpdated(const QGeoPositionInfo &)),
			this,
	    	SLOT(positionUpdatedHandler(const QGeoPositionInfo &)));
	Q_ASSERT(positionUpdatedConnected);
	Q_UNUSED(positionUpdatedConnected);

	m_positionInfoSource->startUpdates();		// start get my location event loop
}

QVariantList WebMaps::worldToPixelInvokable(QObject* mapObject, double lat, double lon) const
{
    MapView* mapview = qobject_cast<MapView*>(mapObject);
    const Point worldCoordinates = Point(lat, lon);
    const QPoint pixels = mapview->worldToWindow(worldCoordinates);

    return QVariantList() << pixels.x() << pixels.y();
}

void WebMaps::updateMarkers(QObject* mapObject, QObject* containerObject) const
{
    MapView* mapview = qobject_cast<MapView*>(mapObject);
    Container* container = qobject_cast<Container*>(containerObject);

    for (int i = 0; i < container->count(); i++) {
        const QPoint xy = worldToPixel(mapview,
                                       container->at(i)->property("lat").value<double>(),
                                       container->at(i)->property("lon").value<double>());
        container->at(i)->setProperty("x", xy.x());
        container->at(i)->setProperty("y", xy.y());
    }
}

void WebMaps::addPin(const QString& ppId, QObject* pinObject)
{
	m_pinMap.insert(ppId, pinObject);
}

QObject* WebMaps::getPin(const QString& ppId) const
{
	QMap<QString, QObject *>::const_iterator it = m_pinMap.find(ppId);
	if (it != m_pinMap.end()) {
		return it.value();
	}

	return 0;
}

QPoint WebMaps::worldToPixel(QObject* mapObject, double latitude, double longitude) const
{
    MapView* mapview = qobject_cast<MapView*>(mapObject);
    const Point worldCoordinates = Point(latitude, longitude);

    return mapview->worldToWindow(worldCoordinates);
}


/*
 * Update GeoLocation update interval to the user specified value
 */
void WebMaps::setGeoLocationInterval(float value)
{
	if (m_positionInfoSource) {
		SystemToast toast;
		stringstream ss;
		ss << "Location Update Interval changed to "
				<< (int)value << " seconds";
		toast.setBody(ss.str().c_str());
		toast.exec();
		m_positionInfoSource->setUpdateInterval((int)value * 1000);
	}
}

/**
 * First, unsubscribe to all subscriptions to friends.
 * Next, start the regular mode timer with user specified frequency.
 */
void WebMaps::setRegularMode()
{
	// unsubscribe all friends
	qDebug() << "unsubscribing...";
	emit unsubscribe();
}

/*
 * First, subscribe to all subscriptions to friends.
 * Next, stop the regular mode timer.
 */
void WebMaps::setRealtimeMode()
{
	// subscribe to all friends
	qDebug() << "subscribing...";
	emit subscribe();
}

/*
 * Signals the WebView control that the location of a friend is updated
 */
void WebMaps::updateFriendLocation(const QString& ppId, double x, double y, int visibility)
{
	if (visibility) {
		emit friendLocationChanged(ppId, x, y, visibility);
	}
}

void WebMaps::positionUpdateTimeout()
{
	if ( m_positionInfoSource->property("replyErrorCode").isValid()  ) {
	    bb::location::PositionErrorCode::Type errorCode
	    	= m_positionInfoSource->property("replyErrorCode").value<bb::location::PositionErrorCode::Type>();
	    qDebug() << "LM Error Code: ";
	    switch ( errorCode ) {
	        // this error code should not be encountered here (included for completeness)
	        case bb::location::PositionErrorCode::None:
	            qDebug() << "None";
	            break;

	        case bb::location::PositionErrorCode::FatalDisabled:
	            qDebug() << "Fatal - disabled (turn on location services!)";
	            break;

	        // this error code should not normally be encountered, may require setting
	        // the reset property to resolve.
	        case bb::location::PositionErrorCode::FatalInsufficientProviders:
	            qDebug() << "Fatal - insufficient providers";
	            break;

	        // this error code could be encountered if an invalid value is set for a
	        // property related to a BB10 Location Manager feature.
	        case bb::location::PositionErrorCode::FatalInvalidRequest:
	            qDebug() << "Fatal - invalid request";
	            break;

	        // the following warning codes are simply to provide more information;
	        // if periodic updates are active they will resume when conditions change.
	        // It may be opportune to inform the user that finding the location is
	        // taking longer than expected.
	        case bb::location::PositionErrorCode::WarnTimeout:
	            qDebug() << "Warning - timeout";
	            break;

	        case bb::location::PositionErrorCode::WarnLostTracking:
	            qDebug() << "Warning - lost tracking";
	            break;

	        default:
	            qWarning() << "Unknown (bad enum value)";
	            break;
	    }
	}
}

void WebMaps::positionUpdatedHandler(const QGeoPositionInfo& update)
{
	myLocation = update.coordinate();

	if (!initialized) {
		emit gotMyLocation(update.coordinate());
		initialized = true;
	} else {
		emit myLocationChanged(myLocation);
	}
}

double WebMaps::getMyLatitude() const
{
	return myLocation.latitude();
}

double WebMaps::getMyLongitude() const
{
	return myLocation.longitude();
}

void WebMaps::startChat(QObject* parent, const QString& pin)
{
	InvokeManager* invokeManager = new InvokeManager(parent);
	InvokeRequest request;
	//request.setTarget("sys.bbm.sharehandler");
	request.setAction("bb.action.BBMCHAT");
	request.setMimeType("text/plain");
	request.setUri(pin);
	request.setTargetTypes(InvokeTarget::Card);
	InvokeTargetReply* reply = invokeManager->invoke(request);
	reply->setParent(parent);
	bool result = connect(reply, SIGNAL(finished()), this, SLOT(onInvokeResult()));
	Q_ASSERT(result);
	result = connect(invokeManager, SIGNAL(childCardDone(const bb::system::CardDoneMessage &)),
			this, SLOT(chatCardDone(const bb::system::CardDoneMessage &)));
	Q_ASSERT(result);
	invokeManager->closeChildCard();
	m_invokeTargetReply = reply;
}

void WebMaps::chatCardDone(const bb::system::CardDoneMessage& msg)
{
	qDebug() << "MSG REASON: " << msg.reason();
}

void WebMaps::onInvokeResult()
{
	// Check for errors
	    switch(m_invokeTargetReply->error()) {
	        // Invocation could not find the target
	        // did we use the right target ID?
	    case InvokeReplyError::NoTarget: {
	            qWarning() << "invokeFinished(): Error: no target";
	            Utility::showToast("invokeFinished(): Error: no target");
	            break;
	        }
	        // There was a problem with the invoke request
	        // did we set all the values correctly?
	    case InvokeReplyError::BadRequest: {
	            qWarning() << "invokeFinished(): Error: bad request";
	            Utility::showToast("invokeFinished(): Error: bad request");
	            break;
	        }
	        // Something went completely
	        // wrong inside the invocation request
	        // Find an alternate route :(
	    case InvokeReplyError::Internal: {
	            qWarning() << "invokeFinished(): Error: internal";
	            Utility::showToast("invokeFinished(): Error: internal");
	            break;
	        }
	        //Message received if the invoke request is successful
	    default:
	        qWarning() << "invokeFinished(): Invoke Succeeded";
	        break;
	    }

	    // A little house keeping never hurts...
	    delete m_invokeTargetReply;
}
