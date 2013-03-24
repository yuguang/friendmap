/*
 * Settings.hpp
 *
 * Manages user profiles and settings such as filtering.
 *
 *  Created on: 2013-03-23
 *      Author: soh
 */

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <QObject>
#include <QString>
#include <QByteArray>
#include <bb/cascades/Image>
#include <bb/platform/bbm/UserStatus>
#include <bb/platform/bbm/ImageType>
#include <bb/system/InvokeTargetReply>
#include <bb/cascades/pickers/FilePicker>

#include "RegistrationHandler.hpp"

namespace bb {
	namespace system {
		class CardDoneMessage;
	}
}
class Settings : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
	Q_PROPERTY(bb::cascades::Image profilePicture READ profilePicture WRITE setProfilePicture NOTIFY profilePictureChanged)
	Q_PROPERTY(QString statusMessage READ statusMessage WRITE setStatusMessage NOTIFY statusMessageChanged)
	Q_PROPERTY(QString personalMessage READ personalMessage WRITE setPersonalMessage NOTIFY personalMessageChanged)

public:
	Settings(QObject* parent, RegistrationHandler* regHandler);
	virtual ~Settings();

	Q_INVOKABLE void show();
	Q_INVOKABLE void openCamera();

	QString displayName();
	bb::cascades::Image profilePicture();
	QString statusMessage();
	QString personalMessage();

public Q_SLOTS:
	void setDisplayName(const QString& displayName);
	void setProfilePicture(const bb::cascades::Image& profilePicture);
	void setProfilePicture(bb::platform::bbm::ImageType::Type mimeType, const QByteArray& profilePicture);
	void setStatusMessage(const QString& statusMessage);
	void setStatusMessage(bb::platform::bbm::UserStatus::Type statusType, const QString& statusMessage);
	void setPersonalMessage(const QString& personalMessage);
	void onCameraInvokeResult();
	void cameraCardDone(const bb::system::CardDoneMessage &);
	void updateProfilePicture(const QStringList &);

signals:
	void displayNameChanged(const QString& displayName);
	void profilePictureChanged(const bb::cascades::Image& profilePicture);
	void statusMessageChanged(const QString& statusMessage);
	void personalMessageChanged(const QString& personalMessage);

private:
	QString m_displayName;
	bb::cascades::Image m_profilePicture;
	QObject* m_parent;
	RegistrationHandler* m_regHandler;
	QString m_statusMessage;
	QString m_personalMessage;
	bb::system::InvokeTargetReply* m_cameraInvokeStatus;
	bb::cascades::pickers::FilePicker* m_filePicker;
};


#endif /* SETTINGS_HPP_ */
