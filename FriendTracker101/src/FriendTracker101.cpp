// Default empty project template
#include "FriendTracker101.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/system/SystemDialog>
#include <bb/platform/bbm/Context>
#include <bb/platform/bbm/RegistrationState>
#include <bps/bps.h>
#include <bps/geolocation.h>
#include <QTimer>


#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <sstream>

using namespace bb::cascades;
using namespace bb::platform::bbm;
using namespace bb::system;
using namespace std;

FriendTracker101::FriendTracker101(const QUuid& uuid, bb::cascades::Application* app)
	: QObject(app)
	, m_context(uuid)
    , m_isAllowed(false)
    , m_progress(BbmRegistrationProgress::NotStarted)
    , m_temporaryError(false)
    , m_statusMessage(tr("Please wait while the application connects to BBM."))
{
    m_nwam = new QNetworkAccessManager(this);
	bool res = connect(m_nwam, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseReply(QNetworkReply*)));
	Q_ASSERT(res);

	if (uuid.isNull()) {
		SystemDialog *uuidDialog = new SystemDialog("OK");
		uuidDialog->setTitle("UUID Error");
		uuidDialog->setBody("Invalid/Empty UUID, please set correctly in main.cpp");
		connect(uuidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
		uuidDialog->show();
		return;
	}
	connect(&m_context,
			SIGNAL(registrationStateUpdated(
				   bb::platform::bbm::RegistrationState::Type)),
			this,
			SLOT(processRegistrationStatus(
				 bb::platform::bbm::RegistrationState::Type)));

	registerApplication();
}

void FriendTracker101::show(){
	QmlDocument * qml = QmlDocument::create("asset:///main.qml").parent(this);
	// Provide access to signals, slots and properties of App to QML
	qml->setContextProperty("_app", this);
	m_root = qml->createRootObject<AbstractPane>();
	Application::instance()->setScene(m_root);

	m_longitude = 9999990;
	m_latitude = 9999990;


	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(getFirstLocation()));
	m_timer->start(1000);
	getFirstLocation();

}

void FriendTracker101::updateLocation(){
	int rc = gpsApi();
	if(rc == 0){
		stringstream ss;
		ss << " (" << m_latitude << ", " << m_longitude << ") ";
		SystemDialog *ppidDialog = new SystemDialog("OK");
		ppidDialog->setTitle("Coordinates");
		ppidDialog->setBody(ss.str().c_str());
		bool res = connect(ppidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
		Q_ASSERT(res);
		ppidDialog->show();

		sendLocationUpdate();
	}else if(rc == -1){
		/*SystemDialog *ppidDialog = new SystemDialog("OK");
		ppidDialog->setTitle("Failure");
		ppidDialog->setBody("Did not receive Geolocation");
		bool res = connect(ppidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
		Q_ASSERT(res);
		ppidDialog->show();*/
	}

}

void FriendTracker101::getFirstLocation(){
	if(!gpsApi()){
		m_timer->stop();
		delete m_timer;
		sendLoginRequest();
		m_timer = new QTimer(this);
		connect(m_timer, SIGNAL(timeout()), this, SLOT(updateLocation()));
		m_timer->start(5000);
	}
}

void FriendTracker101::sendLoginRequest(){
	stringstream jsonStream;
	jsonStream << "{\"ppId\":\"testuser220\",\"x\":" << m_latitude << ", \"y\":" << m_longitude << ",\"friends\":[]}";

	QByteArray jsonString = jsonStream.str().c_str();

	// For your "Content-Length" header
	QByteArray postDataSize = QByteArray::number(jsonString.size());

	// Time for building your request
	QUrl serviceURL("http://friendtracker.org:9000/login");
	QNetworkRequest request(serviceURL);
	// Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
	request.setRawHeader("User-Agent", "FriendTracker v0.1");
	request.setRawHeader("X-Custom-User-Agent", "FriendTracker v0.1");
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Content-Length", postDataSize);

	//connect(m_nwam, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
	m_nwam->post(request, jsonString);
}


void FriendTracker101::sendLocationUpdate(){
	stringstream jsonStream;
	jsonStream << "{\"ppId\":\"testuser220\",\"sessionKey\":\"" << m_sessionKey.toStdString() << "\", \"x\":" << m_latitude << ", \"y\":" << m_longitude << ",\"friends\":[]}";

	QByteArray jsonString = jsonStream.str().c_str();

	// For your "Content-Length" header
	QByteArray postDataSize = QByteArray::number(jsonString.size());

	// Time for building your request
	QUrl serviceURL("http://friendtracker.org:9000/update");
	QNetworkRequest request(serviceURL);
	// Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
	request.setRawHeader("User-Agent", "FriendTracker v0.1");
	request.setRawHeader("X-Custom-User-Agent", "FriendTracker v0.1");
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Content-Length", postDataSize);

	disconnect(m_nwam);
	//connect(m_nwam, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
	m_nwam->post(request, jsonString);

}

void FriendTracker101::parseReply(QNetworkReply* reply){
	if (reply->error() == QNetworkReply::NoError)
	{
		// read data from QNetworkReply here
		QByteArray bytes = reply->readAll();  // bytes
		QString sstring(bytes); // string
		QStringList slist = sstring.split('"');
		if(slist.size() > 7){
			m_sessionKey = slist[7];
		}else if(slist.size() > 3){
			QString status = slist[3];
			Q_ASSERT(status == QString("OK"));
		}
		SystemDialog *ppidDialog = new SystemDialog("OK");
		ppidDialog->setTitle(m_sessionKey);
		ppidDialog->setBody(sstring);
		bool res = connect(ppidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
		Q_ASSERT(res);
		ppidDialog->show();
	}
}

int FriendTracker101::gpsApi(){
	bps_initialize();
	geolocation_request_events(0);
	geolocation_set_period(1);

	int rc = -2;

	double latitude = 999999;
	double longitude = 999999;

	bps_event_t * event = NULL;
	bps_get_event(&event, -1);
	if (event) {
		if (bps_event_get_domain(event) == geolocation_get_domain()) {
			if (event == NULL || bps_event_get_code(event) !=
				GEOLOCATION_INFO) {
				return false;
			}

			latitude = geolocation_event_get_latitude(event);
			longitude = geolocation_event_get_longitude(event);

			if(latitude != m_latitude || longitude != m_longitude){
				m_latitude = latitude;
				m_longitude = longitude;
				rc = 0;
			}



			double accuracy = geolocation_event_get_accuracy(event);

			double altitude = geolocation_event_get_altitude(event);
			bool altitude_valid =
				geolocation_event_is_altitude_valid(event);

			double altitude_accuracy =
				geolocation_event_get_altitude_accuracy(event);
			bool altitude_accuracy_valid =
				geolocation_event_is_altitude_accuracy_valid(event);

			double heading = geolocation_event_get_heading(event);
			bool heading_valid =
				geolocation_event_is_heading_valid(event);

			double speed = geolocation_event_get_speed(event);
			bool speed_valid = geolocation_event_is_speed_valid(event);

			double num_satellites =
				geolocation_event_get_num_satellites_used(event);
			bool num_satellites_valid =
				geolocation_event_is_num_satellites_valid(event);
		}
	}
	geolocation_stop_events(0);

	if(latitude == 999999 && longitude == 999999){
		rc = -1;
	}

	return rc;
}

//! [1]
void FriendTracker101::registerApplication()
{
    m_progress = BbmRegistrationProgress::Started;
    processRegistrationStatus(m_context.registrationState());
}
//! [1]

//! [2]
void FriendTracker101::processRegistrationStatus(const RegistrationState::Type state)
{
    // Based on the state, decide whether we need to register. If we already
    // registered successfully once (i.e. on a previous application run), then
    // we will not call requestRegisterApplication() again.
    qDebug() << "Received a BBM Social Platform registration access state="
        << state;
    switch(m_progress)
    {
    case BbmRegistrationProgress::Pending:
        if (state != RegistrationState::Pending) {
            registrationFinished();
            return;
        }
        // Otherwise, ignore since registration is still in progress.
        break;

    case BbmRegistrationProgress::Started:
        if (m_context.isAccessAllowed()) {
            // Access is allowed, the application is registered.
            registrationFinished();
            return;
        }
        if (m_context.registrationState() == RegistrationState::Unknown) {
            // Status is not yet known. Wait for an event that will deliver the
            // status.
            qDebug() << "BBM Social Platform access state is UNKNOWN; waiting "
                "for the initial status";
            return;
        }
        // Start registration.
        if (m_context.requestRegisterApplication()) {
            // Registration started. The user will see a dialog informing them
            // that your application is connecting to BBM.
            m_progress = BbmRegistrationProgress::Pending;
            qDebug() << "BBM Social Platform registration started";
            qDebug() << "Verify you are using a valid UUID";
            return;
        }
        // Could not start registration. No dialogs were shown.
        qDebug() << "BBM Social Platform registration could not be started";
        registrationFinished();
        break;

    case BbmRegistrationProgress::Finished:
        if (m_context.isAccessAllowed() != m_isAllowed) {
            // Access to the BBM Social Platform has changed.
            registrationFinished();
        }
        break;

    default:
        qDebug() << "Ignoring BBM Social Platform access state=" << state
            << "when progress=" << m_progress;
        break;
    }
}
//![2]

//! [3]
void FriendTracker101::registrationFinished()
{
    // Finish registration and use the state to decide which message to show
    // the user.
    m_progress = BbmRegistrationProgress::Finished;
    SystemDialog *uuidDialog = new SystemDialog("OK");

    switch (m_context.registrationState()) {
    case RegistrationState::Allowed:
        m_statusMessage = tr("Application connected to BBM.  Press Continue.");
        m_temporaryError = false;
        show();
        break;

    case RegistrationState::BlockedByRIM:
        m_statusMessage = tr("Disconnected by RIM. RIM is preventing this "
                             "application from connecting to BBM.");
        m_temporaryError = false;
        uuidDialog->setTitle("Disconnected");
		uuidDialog->setBody("RIM is preventing this application from connecting to BBM");
		connect(uuidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
		uuidDialog->show();
        break;

    case RegistrationState::BlockedByUser:
        m_statusMessage = tr("Disconnected. Go to Settings -> Security and "
                             "Privacy -> Application Permissions and "
                             "connect this application to BBM.");
        m_temporaryError = false;
        uuidDialog->setTitle("Disconnected");
		uuidDialog->setBody("App does not have enough permissions to contact BBM service.");
		connect(uuidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
		uuidDialog->show();
        break;

    case RegistrationState::InvalidUuid:
        // You should be resolving this error at development time.
        m_statusMessage = tr("Invalid UUID. Report this error to the "
                             "vendor.");
        m_temporaryError = true;
        uuidDialog->setTitle("Disconnected");
               	uuidDialog->setBody("Invalid UUID. Report this error to the vendor");
               	connect(uuidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
               	uuidDialog->show();
        break;

    case RegistrationState::MaxAppsReached:
        m_statusMessage = tr("Too many applications are connected to BBM. "
                             "Uninstall one or more applications and try "
                             "again.");
        m_temporaryError = false;
        uuidDialog->setTitle("Disconnected");
               	uuidDialog->setBody("Too many applications are connected to BBM");
               	connect(uuidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
               	uuidDialog->show();
        break;

    case RegistrationState::Expired:
    case RegistrationState::MaxDownloadsReached:
        m_statusMessage = tr("Cannot connect to BBM. Download this "
                             "application from AppWorld to keep using it.");
        m_temporaryError = false;
        break;

    case RegistrationState::NoDataConnection:
        m_statusMessage = tr("Check your Internet connection and try again.");
        m_temporaryError = true;
        uuidDialog->setTitle("Registration Finished");
                               	uuidDialog->setBody("no data");
                               	connect(uuidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
                               	uuidDialog->show();
        break;

    case RegistrationState::Pending:
        // The user will never see this. The BBM Social Platform already
        // displays a "Connecting" dialog.
        m_statusMessage = tr("Connecting to BBM. Please wait.");
        m_temporaryError = false;
        uuidDialog->setTitle("Registration Finished");
                       	uuidDialog->setBody("5");
                       	connect(uuidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
                       	uuidDialog->show();
        break;

    case RegistrationState::Unknown:
        m_statusMessage = tr("Determining the status. Please wait.");
        m_temporaryError = false;
        uuidDialog->setTitle("Registration Finished");
                       	uuidDialog->setBody("4");
                       	connect(uuidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
                       	uuidDialog->show();
        break;

    case RegistrationState::Unregistered:
    case RegistrationState::UnexpectedError:
    case RegistrationState::TemporaryError:
    case RegistrationState::CancelledByUser:
    default:
        // If new error codes are added, treat them as temporary errors.
        m_statusMessage = tr("Would you like to connect the application to "
                             "BBM?");
        m_temporaryError = true;
        uuidDialog->setTitle("Registration Finished");
                       	uuidDialog->setBody("3");
                       	connect(uuidDialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(dialogFinished(bb::system::SystemUiResult::Type)));
                       	uuidDialog->show();
        break;
    }

    if (m_context.isAccessAllowed()) {
        m_isAllowed = true;
    } else {
        m_isAllowed = false;
    }
    qDebug() << "Finished BBM Social Platform registration, success="
        << m_isAllowed << "temporaryError=" << m_temporaryError;
    emit stateChanged();
}
//! [3]

void FriendTracker101::dialogFinished(bb::system::SystemUiResult::Type value) {
	//Application::exit(-1);
}


