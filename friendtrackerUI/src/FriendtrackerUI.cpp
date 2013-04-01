// Navigation pane project template
#include "FriendtrackerUI.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Image>
#include <bb/cascades/Sheet>
#include <bb/cascades/Page>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/GroupDataModel>
#include <bb/platform/bbm/ContactService>
#include <bb/platform/bbm/Contact>
#include <bb/platform/bbm/UserProfile>
#include <bb/platform/bbm/MessageService>
#include <bb/pim/contacts/ContactService>
#include <bb/pim/contacts/Contact>
#include <bb/pim/contacts/ContactListFilters>
#include <bb/system/SystemToast>
#include <bb/ImageData>
#include <bb/utility/ImageConverter>
#include <bb/device/HardwareInfo>

#include <QSettings>

#include "LoginMessage.h"
#include "UpdateLocationMessage.h"
#include "GetLocationsMessage.h"
#include "ServerInterface.h"
#include "Utility.h"
#include "GetAddressHelper.h"
#include "FriendItem.hpp"
#include "MockFriendItem.hpp"

#include <iostream>
#include <sstream>
using namespace std;

using namespace bb::system;
using namespace bb::cascades;
using namespace bb::platform::bbm;

FriendtrackerUI::FriendtrackerUI(bb::cascades::Application *app, const QString& uuid)
: QObject(app)
, m_app(app)
, m_uuid(uuid)
, m_webMaps(0)
, m_webSocketView(new WebSocketView(this))
, m_regHandler(new RegistrationHandler(m_uuid, this))
, m_contactService(0)
, m_profile(0)
, m_sessionKey("")
, m_serverInterface(new ServerInterface(this))
, m_settings(new Settings(this, m_regHandler))
, m_regularModeTimer(new QTimer(this))
, m_visibility(1)
, m_numProfilePictureUpdates(0)
, m_currentMode(realtime)
, m_searchManager(Utility::getSearchManager())
, m_initial(true)

{
	// get user profile when bbm registration succeeds
	bool connected = QObject::connect(m_regHandler, SIGNAL(registered()), this, SLOT(initUserProfile()));
	Q_ASSERT(connected);

	// load main.qml when bbm registration succeeds
	connected = QObject::connect(m_regHandler, SIGNAL(registered()), this, SLOT(initMap()));
	Q_ASSERT(connected);

	// get session key from login
	connected = QObject::connect(m_serverInterface,
			SIGNAL(onSessionKeyChanged(const QString &)),
			this,
			SLOT(setSessionKey(const QString &)));
	Q_ASSERT(connected);

	// get friendlist from login
	connected = QObject::connect(m_serverInterface,
			SIGNAL(onFriendListChanged(const QStringList &)),
			this,
			SLOT(setOnlinePpIds(const QStringList &)));
	Q_ASSERT(connected);

	// get pinlist from login
	connected = QObject::connect(m_serverInterface,
			SIGNAL(onPinListChanged(const QStringList &)),
			this,
			SLOT(setPins(const QStringList &)));
	Q_ASSERT(connected);

	connected = QObject::connect(m_serverInterface,
			SIGNAL(loginFailed()),
			this,
			SLOT(endApplication()));
	Q_ASSERT(connected);

	connected = QObject::connect(m_serverInterface,
			SIGNAL(onGetLocations(const QList<User> &)),
			this,
			SLOT(updateFriendsLocation(const QList<User> &)));
	Q_ASSERT(connected);

    // Connect timer with pull location function to prepare for the regular mode
    connected = connect(m_regularModeTimer, SIGNAL(timeout()),
    		this,
    		SLOT(pullLocations()));
    Q_ASSERT(connected);
	Q_UNUSED(connected);
}

/*
 * Create Map instance here after BBM registration is successful.
 */
void FriendtrackerUI::initMap()
{
	m_webMaps = new WebMaps(this);

	// login when user location is ready
	bool connected = QObject::connect(m_webMaps,
			SIGNAL(gotMyLocation(const QGeoCoordinate &)),
			this,
			SLOT(login(const QGeoCoordinate &)));
	Q_ASSERT(connected);

	// update location whenever user's location is updated (every 5 sec by default?)
	connected = QObject::connect(m_webMaps,
			SIGNAL(myLocationChanged(const QGeoCoordinate &)),
			this,
			SLOT(updateLocation(const QGeoCoordinate &)));
	Q_ASSERT(connected);
	Q_UNUSED(connected);

	// XXX: Looks like we need to register signal/slot before initializing map
	m_webMaps->init();
}

void FriendtrackerUI::login(const QGeoCoordinate& coord)
{
	bb::device::HardwareInfo hardwareInfo;
	LoginMessage msg(m_profile->ppId(),
			coord.latitude(),
			coord.longitude(),
			hardwareInfo.pin(),
			m_ppIds);

	m_serverInterface->sendMessage(msg);
}

void FriendtrackerUI::setSessionKey(const QString& sessionKey)
{
	m_sessionKey = sessionKey;

	// load Map when the session key returns from login reply
	loadMap();
}

void FriendtrackerUI::endApplication()
{
	m_app->exit();
}

void FriendtrackerUI::setOnlinePpIds(const QStringList& ppIds)
{
	// FIXME: it maybe that we should always subscribe to all of user's friends
	//m_onlinePpIds = ppIds;
	m_onlinePpIds = m_ppIds;

	// for testing add testusr1, testusr2, testusr3
	m_onlinePpIds.append(QString("testusr1"));
	m_onlinePpIds.append(QString("testusr2"));
	m_onlinePpIds.append(QString("testusr3"));
}

void FriendtrackerUI::setPins(const QStringList& pins)
{
	m_pins = pins;
	m_pins.append(QString("testpin1"));
	m_pins.append(QString("testpin2"));
	m_pins.append(QString("testpin3"));
}

QStringList FriendtrackerUI::onlinePpIds()
{
	return m_onlinePpIds;
}

QStringList FriendtrackerUI::pins()
{
	return m_pins;
}

QString FriendtrackerUI::getPin(const QString& ppId)
{
	for (int i = 0; i < m_onlinePpIds.size(); i++) {
		if (m_onlinePpIds.at(i) == ppId) {
			return m_pins.at(i);
		}
	}

	return "";
}

void FriendtrackerUI::updateLocation(const QGeoCoordinate& coord)
{
	if (!m_coord.isValid()) {
		m_coord = coord;
	} else {
		// update location when user moves more than 5m
		if (m_coord.isValid() && coord.distanceTo(m_coord) > 5.0) {
			UpdateLocationMessage msg(m_profile->ppId(),
					coord.latitude(),
					coord.longitude(),
					m_visibility,
					m_sessionKey);

			m_serverInterface->sendMessage(msg);

			m_coord = coord;
		}
	}

	emit myLocationUpdated(coord.latitude(), coord.longitude());
}

/*
 * Only changes mode to regular if current mode is realtime
 * Start the regular mode timer (for every timeout, update the user's location)
 */
void FriendtrackerUI::setRegularMode(double frequency)
{
	if (m_currentMode == realtime) {
		m_regularModeTimer->start((int)frequency * 1000);
		m_webMaps->setRegularMode();
		m_currentMode = regular;
	}
}

/*
 * Only changes mode to realtime if current mode is regular
 * Stop the regular mode timer.
 */
void FriendtrackerUI::setRealtimeMode()
{
	if (m_currentMode == regular) {
		m_regularModeTimer->stop();
		m_webMaps->setRealtimeMode();
		m_currentMode = realtime;
	}
}

void FriendtrackerUI::setVisibility(bool visibility)
{
	m_visibility = (visibility ? 1 : 0);

	// use update location request to immediately update visibility
	UpdateLocationMessage msg(m_profile->ppId(),
			m_webMaps->getMyLatitude(),
			m_webMaps->getMyLongitude(),
			m_visibility,
			m_sessionKey);

	m_serverInterface->sendMessage(msg);
}

/*
 * Sends GET msgs for all of user's friends from Redis.
 * Pass locations to WebView control for updating the map.
 */
void FriendtrackerUI::pullLocations()
{
	GetLocationsMessage msg(m_ppIds);
	m_serverInterface->sendMessage(msg);
}

/*
 * Notifies WebMaps class of the user's friends location updates
 */
void FriendtrackerUI::updateFriendsLocation(const QList<User>& friends)
{
	for (int i = 0; i < friends.size(); i++) {
		const User& user = friends.at(i);
		m_webMaps->updateFriendLocation(user.ppId, user.x, user.y, user.visibility);
	}
}

bb::cascades::Image FriendtrackerUI::getProfilePicture()
{
	const QByteArray origImage = m_profile->displayPicture();
	return Utility::scaleImage(origImage, 140, 140);
}

/*
 * This is called when a pin is created for a user with ppId
 */
void FriendtrackerUI::askFriendProfilePicture(const QString& ppId)
{
	QList<Contact> contacts = m_contactService->contacts();
	for (int i = 0; i < contacts.size(); i++) {
		if (contacts.at(i).ppId() == ppId) {
			bool result = m_contactService->requestDisplayPicture(contacts.at(i).handle());
			if (!result) {
				qWarning() << "FAILED TO GET FRIEND's PROFILE PICTURE";
			}
			break;
		}
	}
}

/*
 * A Friend's Profile Picture is asynchronously returned here.
 * Notify main.qml to dynamically update the friend's pin image.
 */
void FriendtrackerUI::returnFriendDisplayPicture(const QString& handle,
												 const bb::platform::bbm::ImageType::Type imageType,
												 const QByteArray& displayPicture)
{
	Q_UNUSED(imageType);
	QByteArray scaledImageInByteArray = Utility::scaleImage(displayPicture, 140, 140);
	QList<Contact> contacts = m_contactService->contacts();
	for (int i = 0; i < contacts.size(); i++) {
		if (contacts.at(i).handle() == handle) {
			emit updateFriendProfilePictureOnMap(contacts.at(i).ppId(), Image(scaledImageInByteArray));
			break;
		}
	}
}

/*
 * When the profile picture changed, save to disk for map to load.
 */
void FriendtrackerUI::updateProfilePicture(const QByteArray& imageData)
{
	m_numProfilePictureUpdates++;
	saveUserProfilePicture(imageData);

	QByteArray scaledImageInByteArray = Utility::scaleImage(imageData, 140, 140);
	emit updateProfilePictureOnMap(Image(scaledImageInByteArray));
}

/*
 * Reads user's profile picture from BBM and then write to disk
 * for loading on the map later.
 */
void FriendtrackerUI::saveUserProfilePicture()
{
	// write an image file with user's profile picture
	UserProfile profile(&m_regHandler->context());
	const QByteArray& displayPicture = profile.displayPicture();

	saveUserProfilePicture(displayPicture);
}

/*
 * Save the given image data in byte array to disk.
 */
void FriendtrackerUI::saveUserProfilePicture(const QByteArray& imageData)
{
	QImage imageToWrite;
	if (!imageToWrite.loadFromData(imageData)) {
		qWarning() << "failed to load profile picture for saving!";
	} else {
		imageToWrite = imageToWrite.scaled(140, 140, Qt::KeepAspectRatio);	// profile picture is 80x80
		stringstream ss;
		ss << "app/native/assets/profile.jpg";
		if (!imageToWrite.save(ss.str().c_str(), "JPG")) {
			qWarning() << "failed to save profile picture!";
		}
	}
}

/*
 * populate GroupDataModel on qml side
 */
GroupDataModel* FriendtrackerUI::friendListModel()
{
	GroupDataModel* groupDataModel = new GroupDataModel(QStringList() << "displayName");

	QList<Contact> contacts = m_contactService->contacts();
	for (QList<Contact>::iterator it = contacts.begin(); it != contacts.end(); ++it) {
		qDebug() << "POPULATE: " << it->displayName();
		groupDataModel->insert(new FriendItem(this, *it, m_contactService, getPin(it->ppId())));
	}

	// Only for testing scenario
	groupDataModel->insert(new MockFriendItem(this, "testusr1", UserStatus::Available, "Available", "I am testusr1!"));
	groupDataModel->insert(new MockFriendItem(this, "testusr2", UserStatus::Available, "Available", "cool weather!"));
	groupDataModel->insert(new MockFriendItem(this, "testusr3", UserStatus::Available, "Available", "I'm hungry!"));

	qDebug() << "POPULATED";

	return groupDataModel;
}

void FriendtrackerUI::loadMap()
{
	qDebug() << "loadMap started";

	// save user's profile before loading the map
	saveUserProfilePicture();
	bool result = connect(m_settings, SIGNAL(profilePictureChanged(const QByteArray &)),
			this, SLOT(updateProfilePicture(const QByteArray &)));
	Q_ASSERT(result);

    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(m_app);
    qml->setContextProperty("_mapView", m_webMaps);
    qml->setContextProperty("_settings", m_settings);
    qml->setContextProperty("_webSocketView", m_webSocketView);
    qml->setContextProperty("_friendtracker", this);

    // create root object for the UI
    NavigationPane *root = qml->createRootObject<NavigationPane>();
    // set created root object as a scene
    m_app->setScene(root);
}

void FriendtrackerUI::getAddress(QObject* containerObject, double lat, double lng, const QString& property)
{
	// FIXME: I know this is a leak
	GetAddressHelper* helper = new GetAddressHelper(containerObject, lat, lng, property);
	Q_UNUSED(helper);
}

/*
 * Initialize Contact Services.
 * Initialize the user's profile and also register a SLOT for
 * displayPictureUpdated() which is emitted when the user's friend's display picture is updated.
 */
void FriendtrackerUI::initUserProfile()
{
	m_profile = new UserProfile(&m_regHandler->context(), this);
	m_contactService = new ContactService(&m_regHandler->context(), 0);

	// send image to main.qml when friend's display picture is updated
	bool connected = QObject::connect(m_contactService, SIGNAL(displayPictureUpdated(const QString &,
			const bb::platform::bbm::ImageType::Type, const QByteArray &)),
			this,
			SLOT(returnFriendDisplayPicture(const QString &,
			const bb::platform::bbm::ImageType::Type, const QByteArray &)));
	Q_ASSERT(connected);
	Q_UNUSED(connected);

	QList<Contact> contacts = m_contactService->contacts();
	QStringList ppIds;
	for (int i = 0; i < contacts.size(); i++) {
		ppIds.append(contacts.at(i).ppId());
	}
	m_ppIds = ppIds;

	emit userProfileInitialized();
}

void FriendtrackerUI::showPin(const QString& ppId)
{
	emit showPinSignal(ppId);
}

void FriendtrackerUI::hidePin(const QString& ppId)
{
	emit hidePinSignal(ppId);
}

QString FriendtrackerUI::getValueFor(const QString &objectName, const QString &defaultValue)
{
    QSettings settings;

    // If no value has been saved, return the default value.
    if (settings.value(objectName).isNull()) {
        return defaultValue;
    }

    // Otherwise, return the value stored in the settings object.
    return settings.value(objectName).toString();
}

void FriendtrackerUI::saveValueFor(const QString &objectName, const QString &inputValue)
{
    // A new value is saved to the application settings object.
    QSettings settings;
    settings.setValue(objectName, QVariant(inputValue));
}

bool FriendtrackerUI::getInitial() {
	return m_initial;
}

void FriendtrackerUI::setInitial(bool initial) {
	qDebug() << "initial is now " << initial;
	m_initial = initial;
}
