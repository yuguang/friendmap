/*
 * FriendItem.hpp
 *
 *  Created on: 2013-03-30
 *      Author: Sukwon Oh
 */

#ifndef FRIENDITEM_HPP_
#define FRIENDITEM_HPP_

#include <QObject>
#include <bb/cascades/Image>
#include <bb/platform/bbm/UserStatus>
#include <bb/platform/bbm/Contact>
#include <bb/platform/bbm/ContactService>

class FriendItem : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
	Q_PROPERTY(bb::cascades::Image profilePicture READ profilePicture NOTIFY profilePictureChanged)
	Q_PROPERTY(bb::platform::bbm::UserStatus::Type userStatus READ userStatus NOTIFY userStatusChanged)
	Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)
	Q_PROPERTY(QString personalMessage READ personalMessage NOTIFY personalMessageChanged)
	Q_PROPERTY(QString ppId READ ppId FINAL)
	Q_PROPERTY(QString pin READ pin FINAL)

public:
	FriendItem(QObject* parent, bb::platform::bbm::Contact& contact, bb::platform::bbm::ContactService* contactService,
			const QString& pin);
	virtual ~FriendItem() {}

	QString displayName() const;
	bb::cascades::Image profilePicture() const;
	bb::platform::bbm::UserStatus::Type userStatus() const;
	QString statusMessage() const;
	QString personalMessage() const;
	QString ppId() const;
	QString pin() const;

public Q_SLOTS:
	void updateFriendDisplayPicture(const QString &, const bb::platform::bbm::ImageType::Type, const QByteArray &);

signals:
	void displayNameChanged(const QString &);
	void profilePictureChanged(const bb::cascades::Image &);
	void userStatusChanged(bb::platform::bbm::UserStatus::Type);
	void statusMessageChanged(const QString &);
	void personalMessageChanged(const QString &);


private:
	bb::platform::bbm::Contact m_contact;
	bb::platform::bbm::ContactService* m_contactService;

	QString m_displayName;
	bb::cascades::Image m_profilePicture;
	bb::platform::bbm::UserStatus::Type m_userStatus;
	QString m_statusMessage;
	QString m_personalMessage;
	QString m_ppId;
	QString m_pin;
};


#endif /* FRIENDLIST_HPP_ */
