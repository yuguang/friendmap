/*
 * Profile.hpp
 *
 *  Created on: 2013-03-23
 *      Author: Sukwon Oh
 */

#ifndef PROFILE_HPP_
#define PROFILE_HPP_

#include <bb/cascades/Image>
#include <bb/platform/bbm/UserProfile>

#include <QtCore/QObject>

class ProfileEditor;
namespace bb {
namespace platform {
namespace bbm {
class Context;
}
}
}
//! [0]
class Profile : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool busy READ busy NOTIFY profileChanged)
    Q_PROPERTY(QString displayName READ displayName NOTIFY profileChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY profileChanged)
    Q_PROPERTY(QString personalMessage READ personalMessage NOTIFY profileChanged)
    Q_PROPERTY(QString ppid READ ppid NOTIFY profileChanged)
    Q_PROPERTY(QString appVersion READ appVersion NOTIFY profileChanged)
    Q_PROPERTY(QString handle READ handle NOTIFY profileChanged)
    Q_PROPERTY(QString platformVersion READ platformVersion NOTIFY profileChanged)
    Q_PROPERTY(QVariant displayPicture READ displayPicture NOTIFY profileChanged)

public:
    Profile(bb::platform::bbm::Context &context, QObject *parent = 0);

public Q_SLOTS:
    void show();
    void requestDisplayPicture();

Q_SIGNALS:
    void profileChanged();

private:
    bool busy() const;
    QString displayName() const;
    QString statusMessage() const;
    QString personalMessage() const;
    QString ppid() const;
    QString appVersion() const;
    QString handle() const;
    QString platformVersion() const;
    QVariant displayPicture() const;
    ProfileEditor* editor() const;

    bb::platform::bbm::UserProfile* m_userProfile;
    bb::cascades::Image m_displayPicture;
    bb::platform::bbm::Context* m_context;
};
//! [0]


#endif /* PROFILE_HPP_ */
