/*
 * FriendItem.hpp
 *
 *  Created on: 2013-03-30
 *      Author: soh
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

	Q_PROPERTY(QString displayName READ displayName FINAL)
	Q_PROPERTY(bb::cascades::Image profilePicture READ profilePicture)
	Q_PROPERTY(bb::platform::bbm::UserStatus::Type userStatus READ userStatus FINAL)
	Q_PROPERTY(QString statusMessage READ statusMessage FINAL)
	Q_PROPERTY(QString personalMessage READ personalMessage FINAL)
	Q_PROPERTY(QString ppId READ ppId FINAL)

public:
	FriendItem(QObject* parent, bb::platform::bbm::Contact& contact, bb::platform::bbm::ContactService* contactService);
	virtual ~FriendItem() {}

	QString displayName() const;
	bb::cascades::Image profilePicture() const;
	bb::platform::bbm::UserStatus::Type userStatus() const;
	QString statusMessage() const;
	QString personalMessage() const;
	QString ppId() const;

public Q_SLOTS:
	void updateFriendDisplayPicture(const QString &, const bb::platform::bbm::ImageType::Type, const QByteArray &);

private:
	bb::platform::bbm::Contact m_contact;
	bb::platform::bbm::ContactService* m_contactService;

	QString m_displayName;
	bb::cascades::Image m_profilePicture;
	bb::platform::bbm::UserStatus::Type m_userStatus;
	QString m_statusMessage;
	QString m_personalMessage;
	QString m_ppId;
};


#endif /* FRIENDLIST_HPP_ */
