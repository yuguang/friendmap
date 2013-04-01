/*
 * Settings.cpp
 *
 *  Created on: 2013-03-23
 *      Author: Sukwon Oh
 */


#include "Settings.hpp"
#include "RegistrationHandler.hpp"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/platform/bbm/UserProfile>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>
#include <bb/system/CardDoneMessage>
#include <bb/system/InvokeTargetReply>
#include <bb/cascades/pickers/FilePicker>
#include <bb/utility/ImageConverter>
#include <bb/system/SystemToast>
#include <bb/ImageData>

#include <bps/soundplayer.h>

#include "Utility.h"

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
, m_userProfile(0)
, m_cameraInvokeStatus(0)
, m_filePicker(0)
, m_initialized(false)
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

/*
 * Called when the user changes from Settings
 */
void Settings::setDisplayName(const QString& displayName)
{
	m_displayName = displayName;
	emit displayNameChanged(displayName);
}

/*
 * Called when the user changes from BBM
 */
void Settings::setDisplayNameFromBBM(const QString& displayName)
{
	m_displayName = displayName;
	emit displayNameChanged(displayName);	// signal to QML view
}

bb::cascades::Image Settings::profilePicture()
{
	return m_profilePicture;
}

/*
 * Called when the user changes from Settings
 */
void Settings::setProfilePicture(const bb::cascades::Image& profilePicture)
{
	m_profilePicture = profilePicture;
	emit profilePictureChangedByUser(m_profilePicture);
}

/*
 * Called when the user changes from BBM
 */
void Settings::setProfilePictureFromBBM(bbm::ImageType::Type mimeType, const QByteArray& profilePicture)
{
	Q_UNUSED(mimeType);
	m_profilePicture = profilePicture;
	emit profilePictureChanged(profilePicture);
}

bbm::UserStatus::Type Settings::userStatus()
{
	return m_userStatus;
}

void Settings::setUserStatus(bbm::UserStatus::Type userStatus)
{
	m_userStatus = userStatus;
	emit userStatusChanged(userStatus);
}

QString Settings::statusMessage()
{
	return m_statusMessage;
}

/*
 * Called when the user changes from Settings
 */
void Settings::setStatusMessage(const QString& statusMessage)
{
	m_statusMessage = statusMessage;
	emit statusMessageChanged(statusMessage);
}

/*
 * Called when the user changes from BBM
 */
void Settings::setStatusFromBBM(bbm::UserStatus::Type statusType, const QString& statusMessage)
{
	m_userStatus = statusType;
	m_statusMessage = statusMessage;

	emit userStatusChanged(statusType);
	emit statusMessageChanged(statusMessage);
}

/*
 * Explicitly used when a user wants to update his status on BBM
 */
void Settings::updateStatusOnBBM()
{
	if ((m_userStatus == 1 && m_statusMessage == "Busy")
			|| (m_userStatus == 2 && m_statusMessage == "Available")) {
		Utility::execToast("You cannot be Available and Busy at the same time!");
		return ;
	}

	bool result = m_userProfile->requestUpdateStatus(m_userStatus, m_statusMessage);
	if (!result) {
		Utility::execToast("Status Update Failed.");
	} else {
		Utility::execToast("Status Updated.");
	}
}

QString Settings::personalMessage()
{
	return m_personalMessage;
}

/*
 * Called when the user changes from Settings
 */
void Settings::setPersonalMessage(const QString& personalMessage)
{
	bool result = m_userProfile->requestUpdatePersonalMessage(personalMessage);
	if (!result) {
		Utility::execToast("Personal Message Update Failed.");
	} else {
		Utility::execToast("Personal Message Updated.");
		m_personalMessage = personalMessage;
		emit personalMessageChanged(personalMessage);
	}
}

/*
 * Called when the user changes from BBM
 */
void Settings::setPersonalMessageFromBBM(const QString& personalMessage)
{
	m_personalMessage = personalMessage;
	emit personalMessageChanged(personalMessage);
}

void Settings::initUserProfileFromBBM()
{
	if (!m_initialized) {
		// get profile info
		m_userProfile = new bbm::UserProfile(&m_regHandler->context());
		bool result = connect(m_userProfile, SIGNAL(displayNameUpdated(const QString &)),
				this, SLOT(setDisplayNameFromBBM(const QString &)));
		Q_ASSERT(result);
		result = connect(m_userProfile, SIGNAL(statusUpdated(bb::platform::bbm::UserStatus::Type, const QString &)),
				this, SLOT(setStatusFromBBM(bb::platform::bbm::UserStatus::Type, const QString &)));
		Q_ASSERT(result);
		result = connect(m_userProfile, SIGNAL(displayPictureUpdated(bb::platform::bbm::ImageType::Type, const QByteArray &)),
				this, SLOT(setProfilePictureFromBBM(bb::platform::bbm::ImageType::Type, const QByteArray &)));
		Q_ASSERT(result);
		result = connect(m_userProfile, SIGNAL(personalMessageUpdated(const QString &)),
				this, SLOT(setPersonalMessageFromBBM(const QString &)));
		Q_ASSERT(result);

		m_displayName = m_userProfile->displayName();
		m_profilePicture = m_userProfile->displayPicture();
		m_userStatus = m_userProfile->status();
		m_statusMessage = m_userProfile->statusMessage();
		m_personalMessage = m_userProfile->personalMessage();

		m_initialized = true;
	}

	// TODO: connect signal to BBM
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
	            qWarning() << "invokeFinished(): Error: no target";
	            break;
	        }
	        // There was a problem with the invoke request
	        // did we set all the values correctly?
	    case InvokeReplyError::BadRequest: {
	            qWarning() << "invokeFinished(): Error: bad request";
	            break;
	        }
	        // Something went completely
	        // wrong inside the invocation request
	        // Find an alternate route :(
	    case InvokeReplyError::Internal: {
	            qWarning() << "invokeFinished(): Error: internal";
	            break;
	        }
	        //Message received if the invoke request is successful
	    default:
	        qWarning() << "invokeFinished(): Invoke Succeeded";
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
	// FIXME: this is an ugly hack. dataType is "" for FilePicker
	// so I am checking that value to determine if I should create FilePicker
	if (message.reason() == "save" && message.dataType() != "") {
		m_filePicker = new FilePicker();
		m_filePicker->setType(FileType::Picture);
		m_filePicker->setTitle("Select Profile Picture");
		m_filePicker->setMode(FilePickerMode::Picker);
		m_filePicker->setImageCropEnabled(true);
		QStringList directories;
		directories.append("/accounts/1000/shared/");
		m_filePicker->setDirectories(directories);
		m_filePicker->open();

		connect(m_filePicker, SIGNAL(fileSelected(const QStringList &)),
				this, SLOT(updateProfilePicture(const QStringList &)));
	}
}

void Settings::updateProfilePicture(const QStringList& images)
{
	// only use first image
	if (images.size() > 0) {
		/*
		 * Update BBM with new Profile Picture
		 */
		QFile file(images.at(0));
		if (!file.open(QIODevice::ReadOnly)) return;
		const QByteArray imageInByteArray = file.readAll();

		QString imageFormat;
		bbm::ImageType::Type imageType = bbm::ImageType::Unsupported;
		if (images.at(0).endsWith(QLatin1String(".jpg"), Qt::CaseInsensitive) ||
				images.at(0).endsWith(QLatin1String(".jpeg"), Qt::CaseInsensitive)) {
			imageFormat = "image/jpeg";
			imageType = bb::platform::bbm::ImageType::Jpg;
		} else if (images.at(0).endsWith(QLatin1String(".png"), Qt::CaseInsensitive)) {
			imageFormat = "image/png";
			imageType = bb::platform::bbm::ImageType::Png;
		} else if (images.at(0).endsWith(QLatin1String(".gif"), Qt::CaseInsensitive)) {
			imageFormat = "image/gif";
			imageType = bb::platform::bbm::ImageType::Gif;
		} else if (images.at(0).endsWith(QLatin1String(".bmp"), Qt::CaseInsensitive)) {
			imageFormat = "image/bmp";
			imageType = bb::platform::bbm::ImageType::Bmp;
		}

		QByteArray scaledImageInByteArray = Utility::scaleImage(imageInByteArray, 300, 300);

		bool result = m_userProfile->requestUpdateDisplayPicture(imageType, scaledImageInByteArray);
		if (!result) {
			Utility::execToast("Failed to set Profile Picture!");
			return;
		} else {
			setProfilePicture(Image(scaledImageInByteArray));
			Utility::execToast("Profile Picture Updated Successfully.");
		}
	}
}
