/****************************************************************************
** Meta object code from reading C++ file 'Settings.hpp'
**
** Created: Mon Apr 1 18:37:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Settings.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Settings.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Settings[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       5,  124, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   10,    9,    9, 0x05,
      65,   50,    9,    9, 0x05,
      99,   50,    9,    9, 0x05,
     159,  148,    9,    9, 0x05,
     228,  214,    9,    9, 0x05,
     277,  258,    9,    9, 0x05,
     359,  343,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     391,   10,    9,    9, 0x0a,
     415,   10,    9,    9, 0x0a,
     446,   50,    9,    9, 0x0a,
     509,  485,    9,    9, 0x0a,
     581,  148,    9,    9, 0x0a,
     632,  214,    9,    9, 0x0a,
     683,  658,    9,    9, 0x0a,
     745,  343,    9,    9, 0x0a,
     773,  343,    9,    9, 0x0a,
     808,    9,    9,    9, 0x0a,
     831,    9,    9,    9, 0x0a,
     875,    9,    9,    9, 0x0a,

 // methods: signature, parameters, type, tag, flags
     909,    9,    9,    9, 0x02,
     934,    9,    9,    9, 0x02,
     947,    9,    9,    9, 0x02,

 // properties: name, type, flags
      10,  967, 0x0a495103,
      50,  975, 0x0049510b,
     148,  995, 0x0049510b,
     214,  967, 0x0a495103,
     343,  967, 0x0a495103,

 // properties: notify_signal_id
       0,
       1,
       3,
       4,
       6,

       0        // eod
};

static const char qt_meta_stringdata_Settings[] = {
    "Settings\0\0displayName\0displayNameChanged(QString)\0"
    "profilePicture\0profilePictureChanged(QByteArray)\0"
    "profilePictureChangedByUser(bb::cascades::Image)\0"
    "userStatus\0"
    "userStatusChanged(bb::platform::bbm::UserStatus::Type)\0"
    "statusMessage\0statusMessageChanged(QString)\0"
    "type,statusMessage\0"
    "statusChangedFromBBM(bb::platform::bbm::UserStatus::Type,QString)\0"
    "personalMessage\0personalMessageChanged(QString)\0"
    "setDisplayName(QString)\0"
    "setDisplayNameFromBBM(QString)\0"
    "setProfilePicture(bb::cascades::Image)\0"
    "mimeType,profilePicture\0"
    "setProfilePictureFromBBM(bb::platform::bbm::ImageType::Type,QByteArray"
    ")\0"
    "setUserStatus(bb::platform::bbm::UserStatus::Type)\0"
    "setStatusMessage(QString)\0"
    "statusType,statusMessage\0"
    "setStatusFromBBM(bb::platform::bbm::UserStatus::Type,QString)\0"
    "setPersonalMessage(QString)\0"
    "setPersonalMessageFromBBM(QString)\0"
    "onCameraInvokeResult()\0"
    "cameraCardDone(bb::system::CardDoneMessage)\0"
    "updateProfilePicture(QStringList)\0"
    "initUserProfileFromBBM()\0openCamera()\0"
    "updateStatusOnBBM()\0QString\0"
    "bb::cascades::Image\0"
    "bb::platform::bbm::UserStatus::Type\0"
};

void Settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Settings *_t = static_cast<Settings *>(_o);
        switch (_id) {
        case 0: _t->displayNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->profilePictureChanged((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->profilePictureChangedByUser((*reinterpret_cast< const bb::cascades::Image(*)>(_a[1]))); break;
        case 3: _t->userStatusChanged((*reinterpret_cast< bb::platform::bbm::UserStatus::Type(*)>(_a[1]))); break;
        case 4: _t->statusMessageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->statusChangedFromBBM((*reinterpret_cast< bb::platform::bbm::UserStatus::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->personalMessageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setDisplayName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->setDisplayNameFromBBM((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->setProfilePicture((*reinterpret_cast< const bb::cascades::Image(*)>(_a[1]))); break;
        case 10: _t->setProfilePictureFromBBM((*reinterpret_cast< bb::platform::bbm::ImageType::Type(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 11: _t->setUserStatus((*reinterpret_cast< bb::platform::bbm::UserStatus::Type(*)>(_a[1]))); break;
        case 12: _t->setStatusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->setStatusFromBBM((*reinterpret_cast< bb::platform::bbm::UserStatus::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->setPersonalMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->setPersonalMessageFromBBM((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->onCameraInvokeResult(); break;
        case 17: _t->cameraCardDone((*reinterpret_cast< const bb::system::CardDoneMessage(*)>(_a[1]))); break;
        case 18: _t->updateProfilePicture((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 19: _t->initUserProfileFromBBM(); break;
        case 20: _t->openCamera(); break;
        case 21: _t->updateStatusOnBBM(); break;
        default: ;
        }
    }
}

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_Settings[] = {
        bb::platform::bbm::UserStatus::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_Settings[] = {
        &bb::platform::bbm::UserStatus::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

const QMetaObjectExtraData Settings::staticMetaObjectExtraData = {
    qt_meta_extradata_Settings,  qt_static_metacall 
};

const QMetaObject Settings::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Settings,
      qt_meta_data_Settings, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Settings::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Settings::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Settings))
        return static_cast<void*>(const_cast< Settings*>(this));
    return QObject::qt_metacast(_clname);
}

int Settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = displayName(); break;
        case 1: *reinterpret_cast< bb::cascades::Image*>(_v) = profilePicture(); break;
        case 2: *reinterpret_cast< bb::platform::bbm::UserStatus::Type*>(_v) = userStatus(); break;
        case 3: *reinterpret_cast< QString*>(_v) = statusMessage(); break;
        case 4: *reinterpret_cast< QString*>(_v) = personalMessage(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDisplayName(*reinterpret_cast< QString*>(_v)); break;
        case 1: setProfilePicture(*reinterpret_cast< bb::cascades::Image*>(_v)); break;
        case 2: setUserStatus(*reinterpret_cast< bb::platform::bbm::UserStatus::Type*>(_v)); break;
        case 3: setStatusMessage(*reinterpret_cast< QString*>(_v)); break;
        case 4: setPersonalMessage(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Settings::displayNameChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Settings::profilePictureChanged(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Settings::profilePictureChangedByUser(const bb::cascades::Image & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Settings::userStatusChanged(bb::platform::bbm::UserStatus::Type _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Settings::statusMessageChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Settings::statusChangedFromBBM(bb::platform::bbm::UserStatus::Type _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Settings::personalMessageChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
