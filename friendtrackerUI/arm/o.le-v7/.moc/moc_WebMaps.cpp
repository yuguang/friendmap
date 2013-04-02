/****************************************************************************
** Meta object code from reading C++ file 'WebMaps.hpp'
**
** Created: Tue Apr 2 11:56:24 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/WebMaps.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebMaps.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WebMaps[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       2,  109, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,    9,    8,    8, 0x05,
      34,   32,    8,    8, 0x05,
      55,    8,    8,    8, 0x05,
      88,   82,    8,    8, 0x05,
     118,   82,    8,    8, 0x05,
     152,    8,    8,    8, 0x05,
     164,    8,    8,    8, 0x05,
     198,  178,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     247,    8,    8,    8, 0x0a,
     276,  271,    8,    8, 0x0a,
     317,    8,    8,    8, 0x0a,
     338,  334,    8,    8, 0x0a,

 // methods: signature, parameters, type, tag, flags
     391,  380,    8,    8, 0x02,
     435,  419,    8,    8, 0x02,
     476,  470,    8,    8, 0x22,
     537,  519,  506,    8, 0x02,
     609,  583,    8,    8, 0x02,
     654,  642,    8,    8, 0x02,
     693,  688,  679,    8, 0x02,

 // properties: name, type, flags
     716,  709, 0x06495001,
     722,  709, 0x06495001,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

static const char qt_meta_stringdata_WebMaps[] = {
    "WebMaps\0\0x\0myLatChanged(double)\0y\0"
    "myLonChanged(double)\0getCurrentLocationFailed()\0"
    "coord\0gotMyLocation(QGeoCoordinate)\0"
    "myLocationChanged(QGeoCoordinate)\0"
    "subscribe()\0unsubscribe()\0ppId,x,y,visibility\0"
    "friendLocationChanged(QString,double,double,int)\0"
    "positionUpdateTimeout()\0info\0"
    "positionUpdatedHandler(QGeoPositionInfo)\0"
    "onInvokeResult()\0msg\0"
    "chatCardDone(bb::system::CardDoneMessage)\0"
    "parent,pin\0startChat(QObject*,QString)\0"
    "value,showToast\0setGeoLocationInterval(float,bool)\0"
    "value\0setGeoLocationInterval(float)\0"
    "QVariantList\0mapObject,lat,lon\0"
    "worldToPixelInvokable(QObject*,double,double)\0"
    "mapObject,containerObject\0"
    "updateMarkers(QObject*,QObject*)\0"
    "ppId,object\0addPin(QString,QObject*)\0"
    "QObject*\0ppId\0getPin(QString)\0double\0"
    "myLat\0myLon\0"
};

void WebMaps::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WebMaps *_t = static_cast<WebMaps *>(_o);
        switch (_id) {
        case 0: _t->myLatChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->myLonChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->getCurrentLocationFailed(); break;
        case 3: _t->gotMyLocation((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 4: _t->myLocationChanged((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 5: _t->subscribe(); break;
        case 6: _t->unsubscribe(); break;
        case 7: _t->friendLocationChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 8: _t->positionUpdateTimeout(); break;
        case 9: _t->positionUpdatedHandler((*reinterpret_cast< const QGeoPositionInfo(*)>(_a[1]))); break;
        case 10: _t->onInvokeResult(); break;
        case 11: _t->chatCardDone((*reinterpret_cast< const bb::system::CardDoneMessage(*)>(_a[1]))); break;
        case 12: _t->startChat((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 13: _t->setGeoLocationInterval((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: _t->setGeoLocationInterval((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: { QVariantList _r = _t->worldToPixelInvokable((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        case 16: _t->updateMarkers((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 17: _t->addPin((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 18: { QObject* _r = _t->getPin((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WebMaps::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WebMaps::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WebMaps,
      qt_meta_data_WebMaps, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WebMaps::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WebMaps::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WebMaps::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebMaps))
        return static_cast<void*>(const_cast< WebMaps*>(this));
    return QObject::qt_metacast(_clname);
}

int WebMaps::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = getMyLatitude(); break;
        case 1: *reinterpret_cast< double*>(_v) = getMyLongitude(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WebMaps::myLatChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WebMaps::myLonChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WebMaps::getCurrentLocationFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void WebMaps::gotMyLocation(const QGeoCoordinate & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WebMaps::myLocationChanged(const QGeoCoordinate & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WebMaps::subscribe()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void WebMaps::unsubscribe()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void WebMaps::friendLocationChanged(const QString & _t1, double _t2, double _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
