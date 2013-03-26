// Navigation pane project template
#include "FriendtrackerUI.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/platform/bbm/ContactService>
#include <bb/platform/bbm/Contact>
#include <bb/platform/bbm/UserProfile>
#include <bb/platform/bbm/MessageService>
#include <bb/pim/contacts/ContactService>
#include <bb/pim/contacts/Contact>
#include <bb/pim/contacts/ContactListFilters>
#include <bb/system/SystemToast>

#include <QSettings>

#include "LoginMessage.h"
#include "UpdateLocationMessage.h"
#include "GetLocationsMessage.h"
#include "ServerInterface.h"

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
, m_webMaps(new WebMaps(this))
, m_regHandler(new RegistrationHandler(m_uuid, m_webMaps, this))
, m_profile(0)
, m_sessionKey("")
, m_serverInterface(new ServerInterface(this))
, m_settings(new Settings(this, m_regHandler))
, m_regularModeTimer(new QTimer(this))
, m_visibility(1)

{
	// get user profile when bbm registration succeeds
	bool connected = QObject::connect(m_regHandler, SIGNAL(registered()), this, SLOT(initUserProfile()));
	Q_ASSERT(connected);

	// load main.qml when bbm registration succeeds
	connected = QObject::connect(m_regHandler, SIGNAL(registered()), this, SLOT(initWebMaps()));
	Q_ASSERT(connected);

	// login when user location is retrieved
	connected = QObject::connect(m_webMaps,
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

void FriendtrackerUI::login(const QGeoCoordinate& coord)
{
	LoginMessage msg(m_profile->ppId(),
			coord.latitude(),
			coord.longitude(),
			m_ppIds);

	m_serverInterface->sendMessage(msg);
}

void FriendtrackerUI::setSessionKey(const QString& sessionKey)
{
	cout << "new session key: " << sessionKey.toStdString() << endl;
	m_sessionKey = sessionKey;
}

void FriendtrackerUI::endApplication()
{
	m_app->exit();
}

void FriendtrackerUI::setOnlinePpIds(const QStringList& ppIds)
{
	cout << "got online ppIds" << endl;
	// FIXME: it maybe that we should always subscribe to all of user's friends
	//m_onlinePpIds = ppIds;
	m_onlinePpIds = m_ppIds;

	// for testing add testusr1, testusr2, testusr3
	m_onlinePpIds.append(QString("testusr1"));
	m_onlinePpIds.append(QString("testusr2"));
	m_onlinePpIds.append(QString("testusr3"));
}

QStringList FriendtrackerUI::onlinePpIds()
{
	return m_onlinePpIds;
}

void FriendtrackerUI::updateLocation(const QGeoCoordinate& coord)
{
	UpdateLocationMessage msg(m_profile->ppId(),
			coord.latitude(),
			coord.longitude(),
			m_visibility,
			m_sessionKey);

	m_serverInterface->sendMessage(msg);
}

/*
 * Start the regular mode timer (for every timeout, update the user's location)
 */
void FriendtrackerUI::setRegularMode(double frequency)
{
	m_regularModeTimer->start((int)frequency * 1000);
	m_webMaps->setRegularMode();
}

/*
 * Stop the regular mode timer.
 */
void FriendtrackerUI::setRealtimeMode()
{
	m_regularModeTimer->stop();
	m_webMaps->setRealtimeMode();
}

void FriendtrackerUI::setVisibility(bool visibility)
{
	m_visibility = (visibility ? 1 : 0);
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

void FriendtrackerUI::initWebMaps()
{
	cout << "initWebMaps started" << endl;
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(m_app);
    qml->setContextProperty("_mapView", m_webMaps);
    qml->setContextProperty("_settings", m_settings);
    qml->setContextProperty("_friendtracker", this);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    m_app->setScene(root);
}

void FriendtrackerUI::initUserProfile()
{
	m_profile = new UserProfile(&m_regHandler->context(), this);
	/*
	cout << "my display name: " << m_profile->displayName().toStdString() << endl;
	cout << "my personal msg: " << m_profile->personalMessage().toStdString() << endl;
	cout << "my status msg: " << m_profile->statusMessage().toStdString() << endl;
	cout << "my ppId: " << m_profile->ppId().toStdString() << endl;
	*/

	ContactService cs(&m_regHandler->context(), 0);
	//if (cs.isValid()) cout << "contact service is valid " << cs.contactCount() << endl;
	QList<Contact> contacts = cs.contacts();
	QStringList ppIds;
	//cout << "getting contacts" << endl;
	for (int i = 0; i < contacts.size(); i++) {
		stringstream ss;
		ss << "ppId: " << contacts.at(i).ppId().toStdString()
		   << " displayName: " << contacts.at(i).displayName().toStdString()
		   << endl;
		cout << ss.str();
		SystemToast toast;
		toast.setBody(QString(ss.str().c_str()));
		toast.exec();
		ppIds.append(contacts.at(i).ppId());
	}
	m_ppIds = ppIds;
	/*using namespace bb::pim;
	bb::pim::contacts::ContactListFilters filter;
	filter = filter.setLimit(10000);
	QList<bb::pim::contacts::Contact> contacts = bb::pim::contacts::ContactService().contacts(filter);
	for (int i = 0; i < contacts.size(); i++) {
		contacts::Contact detailedContact = contacts::ContactService().contactDetails(contacts.at(i).id());
		cout << "name: " << contacts.at(i).displayName().toStdString()
			 << " account id: " << contacts.at(i).accountId() << endl;
		QList<contacts::ContactAttribute> attributes = detailedContact.attributes();
		for (int j = 0; j < attributes.size(); j++) {
			cout << attributes.at(j).label().toStdString() << ": "
					<< attributes.at(j).value().toStdString() << endl;
		}
	}*/

	emit userProfileInitialized();
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
