/****************************************************************************
** Meta object code from reading C++ file 'ServerInterface.h'
**
** Created: Fri Mar 22 13:55:15 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ServerInterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ServerInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ServerInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ServerInterface[] = {
    "ServerInterface\0\0sessionKey\0"
    "loginSuccess(QString)\0parseReply(QNetworkReply*)\0"
};

void ServerInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ServerInterface *_t = static_cast<ServerInterface *>(_o);
        switch (_id) {
        case 0: _t->loginSuccess((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->parseReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ServerInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ServerInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerInterface,
      qt_meta_data_ServerInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ServerInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ServerInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ServerInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServerInterface))
        return static_cast<void*>(const_cast< ServerInterface*>(this));
    return QObject::qt_metacast(_clname);
}

int ServerInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ServerInterface::loginSuccess(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
