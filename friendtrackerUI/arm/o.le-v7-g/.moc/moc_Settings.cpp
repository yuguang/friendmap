/****************************************************************************
** Meta object code from reading C++ file 'Settings.hpp'
**
** Created: Sat Mar 23 21:43:30 2013
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
      15,   14, // methods
       4,   89, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   10,    9,    9, 0x05,
      65,   50,    9,    9, 0x05,
     122,  108,    9,    9, 0x05,
     168,  152,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     200,   10,    9,    9, 0x0a,
     224,   50,    9,    9, 0x0a,
     287,  263,    9,    9, 0x0a,
     352,  108,    9,    9, 0x0a,
     403,  378,    9,    9, 0x0a,
     465,  152,    9,    9, 0x0a,
     493,    9,    9,    9, 0x0a,
     516,    9,    9,    9, 0x0a,
     560,    9,    9,    9, 0x0a,

 // methods: signature, parameters, type, tag, flags
     594,    9,    9,    9, 0x02,
     601,    9,    9,    9, 0x02,

 // properties: name, type, flags
      10,  614, 0x0a495103,
      50,  622, 0x0049510b,
     108,  614, 0x0a495103,
     152,  614, 0x0a495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

static const char qt_meta_stringdata_Settings[] = {
    "Settings\0\0displayName\0displayNameChanged(QString)\0"
    "profilePicture\0"
    "profilePictureChanged(bb::cascades::Image)\0"
    "statusMessage\0statusMessageChanged(QString)\0"
    "personalMessage\0personalMessageChanged(QString)\0"
    "setDisplayName(QString)\0"
    "setProfilePicture(bb::cascades::Image)\0"
    "mimeType,profilePicture\0"
    "setProfilePicture(bb::platform::bbm::ImageType::Type,QByteArray)\0"
    "setStatusMessage(QString)\0"
    "statusType,statusMessage\0"
    "setStatusMessage(bb::platform::bbm::UserStatus::Type,QString)\0"
    "setPersonalMessage(QString)\0"
    "onCameraInvokeResult()\0"
    "cameraCardDone(bb::system::CardDoneMessage)\0"
    "updateProfilePicture(QStringList)\0"
    "show()\0openCamera()\0QString\0"
    "bb::cascades::Image\0"
};

void Settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Settings *_t = static_cast<Settings *>(_o);
        switch (_id) {
        case 0: _t->displayNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->profilePictureChanged((*reinterpret_cast< const bb::cascades::Image(*)>(_a[1]))); break;
        case 2: _t->statusMessageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->personalMessageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setDisplayName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setProfilePicture((*reinterpret_cast< const bb::cascades::Image(*)>(_a[1]))); break;
        case 6: _t->setProfilePicture((*reinterpret_cast< bb::platform::bbm::ImageType::Type(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 7: _t->setStatusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->setStatusMessage((*reinterpret_cast< bb::platform::bbm::UserStatus::Type(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->setPersonalMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->onCameraInvokeResult(); break;
        case 11: _t->cameraCardDone((*reinterpret_cast< const bb::system::CardDoneMessage(*)>(_a[1]))); break;
        case 12: _t->updateProfilePicture((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 13: _t->show(); break;
        case 14: _t->openCamera(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Settings::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = displayName(); break;
        case 1: *reinterpret_cast< bb::cascades::Image*>(_v) = profilePicture(); break;
        case 2: *reinterpret_cast< QString*>(_v) = statusMessage(); break;
        case 3: *reinterpret_cast< QString*>(_v) = personalMessage(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDisplayName(*reinterpret_cast< QString*>(_v)); break;
        case 1: setProfilePicture(*reinterpret_cast< bb::cascades::Image*>(_v)); break;
        case 2: setStatusMessage(*reinterpret_cast< QString*>(_v)); break;
        case 3: setPersonalMessage(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
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
void Settings::profilePictureChanged(const bb::cascades::Image & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Settings::statusMessageChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Settings::personalMessageChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
