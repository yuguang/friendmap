/****************************************************************************
** Meta object code from reading C++ file 'RegistrationHandler.hpp'
**
** Created: Fri Feb 22 20:29:02 2013
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
       4,   14, // methods
       3,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   20,   20,   20, 0x0a,
      64,   58,   20,   20, 0x08,
     140,  134,   20,   20, 0x08,

 // properties: name, type, flags
     194,  189, 0x01495001,
     210,  202, 0x0a495001,
     224,  189, 0x01495001,

 // properties: notify_signal_id
       0,
       0,
       0,

       0        // eod
};

static const char qt_meta_stringdata_RegistrationHandler[] = {
    "RegistrationHandler\0\0stateChanged()\0"
    "registerApplication()\0state\0"
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
        case 1: _t->registerApplication(); break;
        case 2: _t->processRegistrationStatus((*reinterpret_cast< const bb::platform::bbm::RegistrationState::Type(*)>(_a[1]))); break;
        case 3: _t->dialogFinished((*reinterpret_cast< bb::system::SystemUiResult::Type(*)>(_a[1]))); break;
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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
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
QT_END_MOC_NAMESPACE
