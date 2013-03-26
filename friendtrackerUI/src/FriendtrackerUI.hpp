// Navigation pane project template
#ifndef FriendtrackerUI_HPP_
#define FriendtrackerUI_HPP_

#include <QObject>
#include <QList>
#include <QTimer>
#include <bb/platform/bbm/UserProfile>
#include "WebMaps.hpp"
#include "RegistrationHandler.hpp"
#include "Settings.hpp"

#include "GetLocationsReply.h"

#include <QtLocationSubset/QGeoCoordinate>

namespace bb { namespace cascades { class Application; }}

using namespace bb::platform::bbm;
using namespace QtMobilitySubset;

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class FriendtrackerUI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList onlinePpIds READ onlinePpIds WRITE setOnlinePpIds NOTIFY onlinePpIdsChanged)
public:
    FriendtrackerUI(bb::cascades::Application *app, const QString& uuid);
    virtual ~FriendtrackerUI() {}

    Q_INVOKABLE void setRegularMode(double frequency);
    Q_INVOKABLE void setRealtimeMode();
    Q_INVOKABLE void setVisibility(bool);
    Q_INVOKABLE QString getValueFor(const QString &, const QString &);
    Q_INVOKABLE void saveValueFor(const QString &, const QString &);

signals:
	void userProfileInitialized();
	void onlinePpIdsChanged(const QStringList& ppIds);

public Q_SLOTS:
	/**
	 * Wait for BBM registration to succeed before initiating web maps
	 */
	void initWebMaps();
	void initUserProfile();
	void login(const QGeoCoordinate &);
	void updateLocation(const QGeoCoordinate &);
	void setSessionKey(const QString &);
	void endApplication();
	QStringList onlinePpIds();
	void setOnlinePpIds(const QStringList& ppIds);
	void pullLocations();
	void updateFriendsLocation(const QList<User> &);

private:
	bb::cascades::Application* m_app;
	QString m_uuid;
	WebMaps* m_webMaps;
	RegistrationHandler* m_regHandler;
	UserProfile* m_profile;
	QString m_sessionKey;
	ServerInterface* m_serverInterface;
	Settings* m_settings;
	QStringList m_ppIds;
	QStringList m_onlinePpIds;
	QTimer* m_regularModeTimer;
	int m_visibility;
};

#endif /* FriendtrackerUI_HPP_ */
