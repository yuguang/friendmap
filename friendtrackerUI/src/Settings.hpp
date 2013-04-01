/*
 * Settings.hpp
 *
 * Manages user profiles and settings such as filtering.
 *
 *  Created on: 2013-03-23
 *      Author: Sukwon Oh
 */

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <QObject>
#include <QString>
#include <QByteArray>
#include <bb/cascades/Image>
#include <bb/platform/bbm/UserStatus>
#include <bb/platform/bbm/ImageType>

// forward decl
namespace bb {
	namespace system {
		class CardDoneMessage;
		class InvokeTargetReply;
	}
	namespace platform {
		namespace bbm {
			class UserProfile;
		}
	}
	namespace cascades {
		namespace pickers {
			class FilePicker;
		}
	}
}
class RegistrationHandler;

class Settings : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
	Q_PROPERTY(bb::cascades::Image profilePicture READ profilePicture WRITE setProfilePicture NOTIFY profilePictureChanged)
	Q_PROPERTY(bb::platform::bbm::UserStatus::Type userStatus READ userStatus WRITE setUserStatus NOTIFY userStatusChanged)
	Q_PROPERTY(QString statusMessage READ statusMessage WRITE setStatusMessage NOTIFY statusMessageChanged)
	Q_PROPERTY(QString personalMessage READ personalMessage WRITE setPersonalMessage NOTIFY personalMessageChanged)

public:
	Settings(QObject* parent, RegistrationHandler* regHandler);
	virtual ~Settings();

	Q_INVOKABLE void initUserProfileFromBBM();
	Q_INVOKABLE void openCamera();
	Q_INVOKABLE void updateStatusOnBBM();

	QString displayName();
	bb::cascades::Image profilePicture();
	bb::platform::bbm::UserStatus::Type userStatus();
	QString statusMessage();
	QString personalMessage();

public Q_SLOTS:
	void setDisplayName(const QString& displayName);
	void setDisplayNameFromBBM(const QString& displayName);
	void setProfilePicture(const bb::cascades::Image& profilePicture);
	void setProfilePictureFromBBM(bb::platform::bbm::ImageType::Type mimeType, const QByteArray& profilePicture);
	void setUserStatus(bb::platform::bbm::UserStatus::Type userStatus);
	void setStatusMessage(const QString& statusMessage);
	void setStatusFromBBM(bb::platform::bbm::UserStatus::Type statusType, const QString& statusMessage);
	void setPersonalMessage(const QString& personalMessage);
	void setPersonalMessageFromBBM(const QString& personalMessage);
	void onCameraInvokeResult();
	void cameraCardDone(const bb::system::CardDoneMessage &);
	Q_INVOKABLE void updateProfilePicture(const QStringList &);

signals:
	void displayNameChanged(const QString& displayName);
	void profilePictureChanged(const QByteArray& profilePicture);
	void profilePictureChangedByUser(const bb::cascades::Image& profilePicture);
	void userStatusChanged(bb::platform::bbm::UserStatus::Type userStatus);
	void statusMessageChanged(const QString& statusMessage);
	void statusChangedFromBBM(bb::platform::bbm::UserStatus::Type type, const QString& statusMessage);
	void personalMessageChanged(const QString& personalMessage);

private:
	QObject* m_parent;
	RegistrationHandler* m_regHandler;
	bb::platform::bbm::UserProfile* m_userProfile;
	bb::system::InvokeTargetReply* m_cameraInvokeStatus;
	bb::cascades::pickers::FilePicker* m_filePicker;
	bool m_initialized;

	QString m_displayName;
	bb::cascades::Image m_profilePicture;
	bb::platform::bbm::UserStatus::Type m_userStatus;
	QString m_statusMessage;
	QString m_personalMessage;
};


#endif /* SETTINGS_HPP_ */
