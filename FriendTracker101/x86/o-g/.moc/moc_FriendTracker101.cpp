/****************************************************************************
** Meta object code from reading C++ file 'FriendTracker101.hpp'
**
** Created: Sun Feb 24 15:42:49 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/FriendTracker101.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FriendTracker101.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FriendTracker101[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       3,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   33,   17,   17, 0x08,
      72,   66,   17,   17, 0x08,
     121,   17,   17,   17, 0x08,
     138,   17,   17,   17, 0x08,
     157,   17,   17,   17, 0x0a,
     185,  179,   17,   17, 0x08,

 // properties: name, type, flags
     260,  255, 0x01495001,
     276,  268, 0x0a495001,
     290,  255, 0x01495001,

 // properties: notify_signal_id
       0,
       0,
       0,

       0        // eod
};

static const char qt_meta_stringdata_FriendTracker101[] = {
    "FriendTracker101\0\0stateChanged()\0reply\0"
    "parseReply(QNetworkReply*)\0value\0"
    "dialogFinished(bb::system::SystemUiResult::Type)\0"
    "updateLocation()\0getFirstLocation()\0"
    "registerApplication()\0state\0"
    "processRegistrationStatus(bb::platform::bbm::RegistrationState::Type)\0"
    "bool\0allowed\0QString\0statusMessage\0"
    "temporaryError\0"
};

void FriendTracker101::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FriendTracker101 *_t = static_cast<FriendTracker101 *>(_o);
        switch (_id) {
        case 0: _t->stateChanged(); break;
        case 1: _t->parseReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->dialogFinished((*reinterpret_cast< bb::system::SystemUiResult::Type(*)>(_a[1]))); break;
        case 3: _t->updateLocation(); break;
        case 4: _t->getFirstLocation(); break;
        case 5: _t->registerApplication(); break;
        case 6: _t->processRegistrationStatus((*reinterpret_cast< const bb::platform::bbm::RegistrationState::Type(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FriendTracker101::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FriendTracker101::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FriendTracker101,
      qt_meta_data_FriendTracker101, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FriendTracker101::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FriendTracker101::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FriendTracker101::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FriendTracker101))
        return static_cast<void*>(const_cast< FriendTracker101*>(this));
    return QObject::qt_metacast(_clname);
}

int FriendTracker101::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 0: *reinterpret_cast< bool*>(_v) = isAllowed(); break;
        case 1: *reinterpret_cast< QString*>(_v) = statusMessage(); break;
        case 2: *reinterpret_cast< bool*>(_v) = isTemporaryError(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FriendTracker101::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
