/****************************************************************************
** Meta object code from reading C++ file 'MockFriendItem.hpp'
**
** Created: Mon Apr 1 18:37:32 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/MockFriendItem.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MockFriendItem.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MockFriendItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       7,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   16,   15,   15, 0x05,
      55,   49,   15,   15, 0x05,
     103,   98,   15,   15, 0x05,
     172,  158,   15,   15, 0x05,
     218,  202,   15,   15, 0x05,

 // properties: name, type, flags
     258,  250, 0x0a495001,
     290,  270, 0x00495009,
     341,  305, 0x00495009,
     158,  250, 0x0a495001,
     202,  250, 0x0a495001,
     352,  250, 0x0a095001,
     357,  250, 0x0a095001,

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

static const char qt_meta_stringdata_MockFriendItem[] = {
    "MockFriendItem\0\0name\0displayNameChanged(QString)\0"
    "image\0profilePictureChanged(bb::cascades::Image)\0"
    "type\0userStatusChanged(bb::platform::bbm::UserStatus::Type)\0"
    "statusMessage\0statusMessageChanged(QString)\0"
    "personalMessage\0personalMessageChanged(QString)\0"
    "QString\0displayName\0bb::cascades::Image\0"
    "profilePicture\0bb::platform::bbm::UserStatus::Type\0"
    "userStatus\0ppId\0pin\0"
};

void MockFriendItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MockFriendItem *_t = static_cast<MockFriendItem *>(_o);
        switch (_id) {
        case 0: _t->displayNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->profilePictureChanged((*reinterpret_cast< const bb::cascades::Image(*)>(_a[1]))); break;
        case 2: _t->userStatusChanged((*reinterpret_cast< bb::platform::bbm::UserStatus::Type(*)>(_a[1]))); break;
        case 3: _t->statusMessageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->personalMessageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_MockFriendItem[] = {
        bb::platform::bbm::UserStatus::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_MockFriendItem[] = {
        &bb::platform::bbm::UserStatus::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

const QMetaObjectExtraData MockFriendItem::staticMetaObjectExtraData = {
    qt_meta_extradata_MockFriendItem,  qt_static_metacall 
};

const QMetaObject MockFriendItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MockFriendItem,
      qt_meta_data_MockFriendItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MockFriendItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MockFriendItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MockFriendItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MockFriendItem))
        return static_cast<void*>(const_cast< MockFriendItem*>(this));
    return QObject::qt_metacast(_clname);
}

int MockFriendItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
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
void MockFriendItem::displayNameChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MockFriendItem::profilePictureChanged(const bb::cascades::Image & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MockFriendItem::userStatusChanged(bb::platform::bbm::UserStatus::Type _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MockFriendItem::statusMessageChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MockFriendItem::personalMessageChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
