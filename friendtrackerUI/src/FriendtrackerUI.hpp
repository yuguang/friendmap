/**
 * Main mediator class for Friendtracker App
 *
 * Components such as BBM registration, Geolocation, MapView, ServerInterface talks to
 * this class to communicate with other components.
 *
 * by Sukwon Oh
 */
#ifndef FriendtrackerUI_HPP_
#define FriendtrackerUI_HPP_

#include <QObject>
#include <QList>
#include <QTimer>
#include <bb/platform/bbm/UserProfile>
#include "WebMaps.hpp"
#include "RegistrationHandler.hpp"
#include "Settings.hpp"
#include "WebSocketView.hpp"

#include "GetLocationsReply.h"

#include <QtLocationSubset/QGeoCoordinate>

// forward decl
namespace bb {
	namespace cascades {
		class Application;
		class GroupDataModel;
	}
}
namespace bb {
	namespace platform {
		namespace bbm {
			class ContactService;
		}
	}
}

using namespace bb::platform::bbm;
using namespace QtMobilitySubset;


/**
 * Main app class
 */
class FriendtrackerUI : public QObject
{
    Q_OBJECT

    /*
     * List of user's friends ppIds
     */
    Q_PROPERTY(QStringList onlinePpIds READ onlinePpIds WRITE setOnlinePpIds NOTIFY onlinePpIdsChanged)
    Q_PROPERTY(bb::cascades::GroupDataModel* friendListModel READ friendListModel)

public:
    FriendtrackerUI(bb::cascades::Application *app, const QString& uuid);
    virtual ~FriendtrackerUI() {}

    /*
     * unsubscribe to realtime updates and starts a timer for regular location pulling with given frequency
     */
    Q_INVOKABLE void setRegularMode(double frequency);

    /*
     * subscribe to realtime updates and cancel a timer for regular location pulling
     */
    Q_INVOKABLE void setRealtimeMode();

    /*
     * set visibility of the user
     */
    Q_INVOKABLE void setVisibility(bool);

    /*
     * get value of previously saved setting
     */
    Q_INVOKABLE QString getValueFor(const QString &, const QString &);

    /*
     * save a value for the given setting
     */
    Q_INVOKABLE void saveValueFor(const QString &, const QString &);

    /*
     * asynchronously lookup the person's address and update the bubble (containerObject)
     */
    Q_INVOKABLE void getAddress(QObject* containerObject, double x, double y);

    /*
     * get profile picture
     */
    Q_INVOKABLE bb::cascades::Image getProfilePicture();

    /*
     * asynchronously request for friend's display picture
     */
    Q_INVOKABLE void askFriendProfilePicture(const QString &);

signals:
	void userProfileInitialized();

	/*
	 * should be connected to a slot to update friends list on websocket.js
	 */
	void onlinePpIdsChanged(const QStringList& ppIds);

	/*
	 * user's profile picture changed signal
	 */
	void updateProfilePictureOnMap(const bb::cascades::Image &);

	/*
	 * friend's profile picture changed signal
	 */
	void updateFriendProfilePictureOnMap(const QString& ppId, const bb::cascades::Image &);

public Q_SLOTS:
	/**
	 * Wait for BBM registration to succeed before initiating mapView
	 */
	void initMap();

	/*
	 * actually load mapView on qml
	 */
	void loadMap();

	/*
	 * get the user's profile
	 */
	void initUserProfile();

	/*
	 * send login request
	 */
	void login(const QGeoCoordinate &);

	/*
	 * send update location request
	 */
	void updateLocation(const QGeoCoordinate &);

	/*
	 * assign a session key from login reply
	 */
	void setSessionKey(const QString &);

	/*
	 * terminate applicatino on receiving this signal
	 */
	void endApplication();

	QStringList onlinePpIds();
	void setOnlinePpIds(const QStringList& ppIds);

	/*
	 * send pull locations request
	 */
	void pullLocations();

	/*
	 * update all friends locations
	 */
	void updateFriendsLocation(const QList<User>& friends);

	/*
	 * update profile picture
	 */
	void updateProfilePicture(const QByteArray &);

	/*
	 * returns friend's display picture from askFriendProfilePicture request
	 */
	void returnFriendDisplayPicture(const QString &, const bb::platform::bbm::ImageType::Type, const QByteArray &);

	/*
	 * populates a GroupDataModel of the user's friend list on qml side
	 */
	bb::cascades::GroupDataModel* friendListModel();


private:
	/*
	 * save user's profile picture straight from BBM
	 */
	void saveUserProfilePicture();

	/*
	 * save user's profile picture to given image
	 */
	void saveUserProfilePicture(const QByteArray &);

private:
	/*
	 * operation mode
	 */
	enum Mode {
		realtime,
		regular
	};

	bb::cascades::Application* m_app;
	QString m_uuid;
	WebMaps* m_webMaps;
	WebSocketView* m_webSocketView;
	RegistrationHandler* m_regHandler;
	bb::platform::bbm::ContactService* m_contactService;
	UserProfile* m_profile;
	QString m_sessionKey;
	ServerInterface* m_serverInterface;
	Settings* m_settings;
	QStringList m_ppIds;
	QStringList m_onlinePpIds;
	QTimer* m_regularModeTimer;
	int m_visibility;
	int m_numProfilePictureUpdates;
	QString m_previousProfilePicturePath;
	Mode m_currentMode;
};

#endif /* FriendtrackerUI_HPP_ */
