/*
 * Settings.cpp
 *
 *  Created on: 2013-03-23
 *      Author: soh
 */


#include "Settings.hpp"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/platform/bbm/UserProfile>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>
#include <bb/system/CardDoneMessage>

#include <bps/soundplayer.h>

#include <iostream>

using namespace std;

using namespace bb::cascades;
using namespace bb::platform;
using namespace bb::system;
using namespace bb::cascades::pickers;

Settings::Settings(QObject* parent, RegistrationHandler* regHandler)
: QObject(parent)
, m_parent(parent)
, m_regHandler(regHandler)
, m_cameraInvokeStatus(0)
, m_filePicker(0)
{
	//qmlRegisterType < Camera > ("bb.cascades.multimedia", 1, 0, "Camera");
}

Settings::~Settings()
{

}

QString Settings::displayName()
{
	return m_displayName;
}

void Settings::setDisplayName(const QString& displayName)
{
	m_displayName = displayName;
	emit displayNameChanged(displayName);
}

bb::cascades::Image Settings::profilePicture()
{
	return m_profilePicture;
}

void Settings::setProfilePicture(const bb::cascades::Image& profilePicture)
{
	m_profilePicture = profilePicture;
	emit profilePictureChanged(profilePicture);
}

void Settings::setProfilePicture(bbm::ImageType::Type mimeType, const QByteArray& profilePicture)
{
	Q_UNUSED(mimeType);
	setProfilePicture(profilePicture);
}

QString Settings::statusMessage()
{
	return m_statusMessage;
}

void Settings::setStatusMessage(const QString& statusMessage)
{
	m_statusMessage = statusMessage;
	emit statusMessageChanged(statusMessage);
}

void Settings::setStatusMessage(bbm::UserStatus::Type statusType, const QString& statusMessage)
{
	Q_UNUSED(statusType);
	setStatusMessage(statusMessage);
}

QString Settings::personalMessage()
{
	return m_personalMessage;
}

void Settings::setPersonalMessage(const QString& personalMessage)
{
	m_personalMessage = personalMessage;
	emit personalMessageChanged(personalMessage);
}

void Settings::show()
{
	// get profile info
	bbm::UserProfile* profile = new bbm::UserProfile(&m_regHandler->context());
	bool result = connect(profile, SIGNAL(displayNameUpdated(const QString &)),
			this, SLOT(setDisplayName(const QString &)));
	Q_ASSERT(result);
	result = connect(profile, SIGNAL(statusUpdated(bb::platform::bbm::UserStatus::Type, const QString &)),
			this, SLOT(setStatusMessage(bb::platform::bbm::UserStatus::Type, const QString &)));
	Q_ASSERT(result);
	result = connect(profile, SIGNAL(displayPictureUpdated(bb::platform::bbm::ImageType::Type, const QByteArray &)),
			this, SLOT(setProfilePicture(bb::platform::bbm::ImageType::Type, const QByteArray &)));
	Q_ASSERT(result);
	result = connect(profile, SIGNAL(personalMessageUpdated(const QString &)),
			this, SLOT(setPersonalMessage(const QString &)));
	Q_ASSERT(result);

	m_displayName = profile->displayName();
	m_profilePicture = profile->displayPicture();
	m_statusMessage = profile->statusMessage();
	m_personalMessage = profile->personalMessage();

	QmlDocument* qml = QmlDocument::create("asset:///settings.qml").parent(this);
	qml->setContextProperty("_settings", this);
	AbstractPane* root = qml->createRootObject<AbstractPane>();
	Application::instance()->setScene(root);
}

/**
 * Open up a camera for taking Profile Picture
 */
void Settings::openCamera()
{
	InvokeManager* invokeManager = new InvokeManager(this);
	InvokeRequest request;
	request.setTarget("sys.camera.card");
	request.setAction("bb.action.CAPTURE");
	request.setData("photo");
	request.setTargetTypes(InvokeTarget::Card);
	InvokeTargetReply* reply = invokeManager->invoke(request);
	reply->setParent(this);
	connect(reply, SIGNAL(finished()), this, SLOT(onCameraInvokeResult()));
	connect(invokeManager, SIGNAL(childCardDone(const bb::system::CardDoneMessage &)),
			this, SLOT(cameraCardDone(const bb::system::CardDoneMessage &)));
	m_cameraInvokeStatus = reply;
}

void Settings::onCameraInvokeResult()
{
	// Check for errors
	    switch(m_cameraInvokeStatus->error()) {
	        // Invocation could not find the target
	        // did we use the right target ID?
	    case InvokeReplyError::NoTarget: {
	            cout << "invokeFinished(): Error: no target" << endl;
	            break;
	        }
	        // There was a problem with the invoke request
	        // did we set all the values correctly?
	    case InvokeReplyError::BadRequest: {
	            cout << "invokeFinished(): Error: bad request" << endl;
	            break;
	        }
	        // Something went completely
	        // wrong inside the invocation request
	        // Find an alternate route :(
	    case InvokeReplyError::Internal: {
	            cout << "invokeFinished(): Error: internal" << endl;
	            break;
	        }
	        //Message received if the invoke request is successful
	    default:
	        cout << "invokeFinished(): Invoke Succeeded" << endl;
	        break;
	    }

	    // A little house keeping never hurts...
	    delete m_cameraInvokeStatus;
}

/**
 * Camera cards responses
 * done - card is closed without initiating a capture
 * close - card closes due to error
 * save - card is closed after user takes a photo
 */
void Settings::cameraCardDone(const bb::system::CardDoneMessage& message)
{
	cout << "REASON: " << message.reason().toStdString() << endl;
	cout << "MESSAGE: " << message.data().toStdString() << endl;
	cout << "Type: " << message.dataType().toStdString() << endl;

	// FIXME: this is an ugly hack. dataType is "" for FilePicker
	// so I am checking that value to determine if I should create FilePicker
	if (message.reason() == "save" && message.dataType() != "") {
		m_filePicker = new FilePicker();
		m_filePicker->setType(FileType::Picture);
		m_filePicker->setTitle("Select Profile Picture");
		m_filePicker->setMode(FilePickerMode::Picker);
		m_filePicker->setImageCropEnabled(true);
		m_filePicker->open();

		connect(m_filePicker, SIGNAL(fileSelected(const QStringList &)),
				this, SLOT(updateProfilePicture(const QStringList &)));
	}
}

void Settings::updateProfilePicture(const QStringList& images)
{
	// only use first image
	if (images.size() > 0) {
		cout << "UPDATE: " << images.at(0).toStdString() << endl;
		setProfilePicture(Image(images.at(0)));
	}
}
