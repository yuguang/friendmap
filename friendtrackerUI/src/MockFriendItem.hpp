/*
 * MockFriendItem.hpp
 *
 *  Created on: 2013-03-30
 *      Author: soh
 */

#ifndef MOCKFRIENDITEM_HPP_
#define MOCKFRIENDITEM_HPP_

#include <QObject>
#include <bb/cascades/Image>
#include <bb/platform/bbm/UserStatus>

class MockFriendItem : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
	Q_PROPERTY(bb::cascades::Image profilePicture READ profilePicture NOTIFY profilePictureChanged)
	Q_PROPERTY(bb::platform::bbm::UserStatus::Type userStatus READ userStatus NOTIFY userStatusChanged)
	Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)
	Q_PROPERTY(QString personalMessage READ personalMessage NOTIFY personalMessageChanged)
	Q_PROPERTY(QString ppId READ ppId)

public:
	MockFriendItem(QObject* parent,
			const QString& displayName,
			bb::platform::bbm::UserStatus::Type,
			const QString& statusMessage,
			const QString& personalMessage);

	virtual ~MockFriendItem() {}

	QString displayName() const;
	bb::cascades::Image profilePicture() const;
	bb::platform::bbm::UserStatus::Type userStatus() const;
	QString statusMessage() const;
	QString personalMessage() const;
	QString ppId() const;

signals:
	void displayNameChanged(const QString& name);
	void profilePictureChanged(const bb::cascades::Image& image);
	void userStatusChanged(bb::platform::bbm::UserStatus::Type type);
	void statusMessageChanged(const QString& statusMessage);
	void personalMessageChanged(const QString& personalMessage);

private:
	QString m_displayName;
	bb::cascades::Image m_profilePicture;
	bb::platform::bbm::UserStatus::Type m_userStatus;
	QString m_statusMessage;
	QString m_personalMessage;
	QString m_ppId;
};


#endif /* MOCKFRIENDITEM_HPP_ */
