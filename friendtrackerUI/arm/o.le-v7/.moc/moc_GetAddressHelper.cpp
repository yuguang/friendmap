/****************************************************************************
** Meta object code from reading C++ file 'GetAddressHelper.h'
**
** Created: Mon Apr 1 18:37:30 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/GetAddressHelper.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GetAddressHelper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GetAddressHelper[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x0a,
      81,   56,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GetAddressHelper[] = {
    "GetAddressHelper\0\0reply\0"
    "searchResults(QGeoSearchReply*)\0"
    "reply,error,errorMessage\0"
    "searchError(QGeoSearchReply*,QGeoSearchReply::Error,QString)\0"
};

void GetAddressHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GetAddressHelper *_t = static_cast<GetAddressHelper *>(_o);
        switch (_id) {
        case 0: _t->searchResults((*reinterpret_cast< QGeoSearchReply*(*)>(_a[1]))); break;
        case 1: _t->searchError((*reinterpret_cast< QGeoSearchReply*(*)>(_a[1])),(*reinterpret_cast< QGeoSearchReply::Error(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GetAddressHelper::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GetAddressHelper::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GetAddressHelper,
      qt_meta_data_GetAddressHelper, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GetAddressHelper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GetAddressHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GetAddressHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GetAddressHelper))
        return static_cast<void*>(const_cast< GetAddressHelper*>(this));
    return QObject::qt_metacast(_clname);
}

int GetAddressHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
