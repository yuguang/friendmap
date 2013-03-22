// Navigation pane project template
#ifndef FriendtrackerUI_HPP_
#define FriendtrackerUI_HPP_

#include <QObject>
#include <bb/platform/bbm/UserProfile>
#include "WebMaps.hpp"
#include "RegistrationHandler.hpp"

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
public:
    FriendtrackerUI(bb::cascades::Application *app, const QString& uuid);
    virtual ~FriendtrackerUI() {}

signals:
	void userProfileInitialized();

public Q_SLOTS:
	/**
	 * Wait for BBM registration to succeed before initiating web maps
	 */
	void initWebMaps();
	void initUserProfile();
	void login(const QGeoCoordinate &);
	void updateLocation(const QGeoCoordinate &);
	void setSessionKey(const QString &);

private:
	bb::cascades::Application* m_app;
	QString m_uuid;
	WebMaps* m_webMaps;
	RegistrationHandler* m_regHandler;
	UserProfile* m_profile;
	QString m_sessionKey;
	ServerInterface* m_serverInterface;

};

#endif /* FriendtrackerUI_HPP_ */
