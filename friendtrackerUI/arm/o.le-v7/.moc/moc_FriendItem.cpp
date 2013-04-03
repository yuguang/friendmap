/****************************************************************************
** Meta object code from reading C++ file 'FriendItem.hpp'
**
** Created: Tue Apr 2 20:35:30 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/FriendItem.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FriendItem.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FriendItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       7,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      40,   11,   11,   11, 0x05,
      83,   11,   11,   11, 0x05,
     138,   11,   11,   11, 0x05,
     168,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     203,  200,   11,   11, 0x0a,
     299,  285,   11,   11, 0x0a,

 // properties: name, type, flags
     330,  322, 0x0a495001,
     362,  342, 0x00495009,
     413,  377, 0x00495009,
     424,  322, 0x0a495001,
     438,  322, 0x0a495001,
     454,  322, 0x0a095801,
     459,  322, 0x0a095801,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       0,
       0,

       0        // eod
};

static const char qt_meta_stringdata_FriendItem[] = {
    "FriendItem\0\0displayNameChanged(QString)\0"
    "profilePictureChanged(bb::cascades::Image)\0"
    "userStatusChanged(bb::platform::bbm::UserStatus::Type)\0"
    "statusMessageChanged(QString)\0"
    "personalMessageChanged(QString)\0,,\0"
    "updateFriendDisplayPicture(QString,bb::platform::bbm::ImageType::Type,"
    "QByteArray)\0"
    "contactHandle\0updateContact(QString)\0"
    "QString\0displayName\0bb::cascades::Image\0"
    "profilePicture\0bb::platform::bbm::UserStatus::Type\0"
    "userStatus\0statusMessage\0personalMessage\0"
    "ppId\0pin\0"
};

void FriendItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FriendItem *_t = static_cast<FriendItem *>(_o);
        switch (_id) {
        case 0: _t->displayNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->profilePictureChanged((*reinterpret_cast< const bb::cascades::Image(*)>(_a[1]))); break;
        case 2: _t->userStatusChanged((*reinterpret_cast< bb::platform::bbm::UserStatus::Type(*)>(_a[1]))); break;
        case 3: _t->statusMessageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->personalMessageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateFriendDisplayPicture((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const bb::platform::bbm::ImageType::Type(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 6: _t->updateContact((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_FriendItem[] = {
        bb::platform::bbm::UserStatus::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_FriendItem[] = {
        &bb::platform::bbm::UserStatus::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

const QMetaObjectExtraData FriendItem::staticMetaObjectExtraData = {
    qt_meta_extradata_FriendItem,  qt_static_metacall 
};

const QMetaObject FriendItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FriendItem,
      qt_meta_data_FriendItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FriendItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FriendItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FriendItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FriendItem))
        return static_cast<void*>(const_cast< FriendItem*>(this));
    return QObject::qt_metacast(_clname);
}

int FriendItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
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
        case 5: *reinterpret_cast< QString*>(_v) = ppId(); break;
        case 6: *reinterpret_cast< QString*>(_v) = pin(); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FriendItem::displayNameChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FriendItem::profilePictureChanged(const bb::cascades::Image & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FriendItem::userStatusChanged(bb::platform::bbm::UserStatus::Type _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FriendItem::statusMessageChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FriendItem::personalMessageChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
