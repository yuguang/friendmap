// Default empty project template
#ifndef FriendTracker101_HPP_
#define FriendTracker101_HPP_

#include <bb/system/SystemUiResult>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QtCore/QObject>
#include <bb/platform/bbm/UserProfile>
#include <bb/cascades/AbstractPane>
#include <QTimer>

#include <bb/platform/bbm/Context>
#include <bb/platform/bbm/RegistrationState>
#include <bb/system/SystemUiResult>
#include <QUuid>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class FriendTracker101 : public QObject
{
    Q_OBJECT

    // Flag indicating whether the application is successfully registered
    // with BBM.
    Q_PROPERTY(bool allowed READ isAllowed NOTIFY stateChanged)

    // The status message describing the registration process.
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY stateChanged)

    // Flag indicating whether registration failed due to a temporary error.
    // This allows the user to re-try registration.
    Q_PROPERTY(bool temporaryError READ isTemporaryError NOTIFY stateChanged)

public:
    //FriendTracker101(bb::platform::bbm::Context * ctx = 0, QObject *app = 0);
    FriendTracker101(const QUuid& uuid, bb::cascades::Application *app = 0);
    virtual ~FriendTracker101() {}
    void show();


private Q_SLOTS:
	void parseReply(QNetworkReply* reply);
    void dialogFinished(bb::system::SystemUiResult::Type value);

    void updateLocation();
    void getFirstLocation();


private:
    int gpsApi();
    void sendLocationUpdate();
    void sendLoginRequest();

    QNetworkAccessManager * m_nwam;
    bb::cascades::AbstractPane *m_root;
    QString m_sessionKey;
    double m_latitude;
    double m_longitude;
    QTimer* m_timer;



public:
    // Enumerates the possible registration progress states.
    struct BbmRegistrationProgress
    {
        enum Type {
            // Registration has not started and has never been attempted since
            // the application started.
            NotStarted = 0,
            // Registration has started.
            Started,
            // Registration is in progress.
            Pending,
            // Registration is done. Use isRegistered() or
            // Context::isAccessAllowed() to check if the application is
            // registered successfully.
            Finished
        };
    };

    /**
     * Returns the BBM context that is associated with this application.
     */
    bb::platform::bbm::Context& context()
    { return m_context; }

    /**
     * Returns the registration progress.
     * @see BbmRegistrationProgress::Type
     */
    BbmRegistrationProgress::Type progress() const
    { return m_progress; }

public Q_SLOTS:
    /**
     * This method is called to trigger the registration with the BBM Social
     * Platform. Check the progress prior to calling this function to ensure
     * that another registration is not in progress.
     */
    void registerApplication();


Q_SIGNALS:
    // The change notification signal of the properties.
    void stateChanged();

private Q_SLOTS:
    // This slot is invoked whenever the registration status is changed.
    // This will initiate, continue, or finish registration based on the status.
    // @param state is the registration state
    void processRegistrationStatus(const bb::platform::bbm::RegistrationState::Type state);

private:
    // Return true if registration has completed successfully.
    bool isAllowed() const
    { return m_isAllowed; }

    // Return true if registration failed due to a temporary error.
    bool isTemporaryError() const
    { return m_temporaryError; }

    // Return the message that describes the registration state.
    const QString& statusMessage() const
    { return m_statusMessage; }

    // Registration finished. This method updates m_registered, m_statusMessage,
    // and m_progress. It emits a stateChanged() signal.
    void registrationFinished();

    // BBM Social Platform Context used to gain access to BBM functionality.
    bb::platform::bbm::Context m_context;

    // A flag that indicates whether registration completed successfully.
    bool m_isAllowed;

    // Registration progress. Use this to check if you have already attempted
    // registration, if registration has finished, or it's still in progress.
    BbmRegistrationProgress::Type m_progress;

    // A flag that indicates whether registration failed due to a temporary
    // error.
    bool m_temporaryError;

    // A status message that describes the current state of registration.
    QString m_statusMessage;

};


#endif /* FriendTracker101_HPP_ */
