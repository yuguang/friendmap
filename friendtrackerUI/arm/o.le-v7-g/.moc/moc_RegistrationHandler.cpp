/****************************************************************************
** Meta object code from reading C++ file 'RegistrationHandler.hpp'
**
** Created: Fri Mar 22 13:55:12 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/RegistrationHandler.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RegistrationHandler.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RegistrationHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       3,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      36,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   20,   20,   20, 0x0a,
      71,   20,   20,   20, 0x0a,
      98,   92,   20,   20, 0x08,
     174,  168,   20,   20, 0x08,

 // properties: name, type, flags
     228,  223, 0x01495001,
     244,  236, 0x0a495001,
     258,  223, 0x01495001,

 // properties: notify_signal_id
       0,
       0,
       0,

       0        // eod
};

static const char qt_meta_stringdata_RegistrationHandler[] = {
    "RegistrationHandler\0\0stateChanged()\0"
    "registered()\0registerApplication()\0"
    "finishRegistration()\0state\0"
    "processRegistrationStatus(bb::platform::bbm::RegistrationState::Type)\0"
    "value\0dialogFinished(bb::system::SystemUiResult::Type)\0"
    "bool\0allowed\0QString\0statusMessage\0"
    "temporaryError\0"
};

void RegistrationHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RegistrationHandler *_t = static_cast<RegistrationHandler *>(_o);
        switch (_id) {
        case 0: _t->stateChanged(); break;
        case 1: _t->registered(); break;
        case 2: _t->registerApplication(); break;
        case 3: _t->finishRegistration(); break;
        case 4: _t->processRegistrationStatus((*reinterpret_cast< const bb::platform::bbm::RegistrationState::Type(*)>(_a[1]))); break;
        case 5: _t->dialogFinished((*reinterpret_cast< bb::system::SystemUiResult::Type(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RegistrationHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RegistrationHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RegistrationHandler,
      qt_meta_data_RegistrationHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RegistrationHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RegistrationHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RegistrationHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RegistrationHandler))
        return static_cast<void*>(const_cast< RegistrationHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int RegistrationHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
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
void RegistrationHandler::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RegistrationHandler::registered()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
