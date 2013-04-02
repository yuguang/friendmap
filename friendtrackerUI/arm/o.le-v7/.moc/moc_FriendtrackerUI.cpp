/****************************************************************************
** Meta object code from reading C++ file 'FriendtrackerUI.hpp'
**
** Created: Tue Apr 2 12:32:57 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/FriendtrackerUI.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FriendtrackerUI.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FriendtrackerUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       4,  204, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      48,   42,   16,   16, 0x05,
      85,   80,   16,   16, 0x05,
     110,   16,   16,   16, 0x05,
     163,  157,   16,   16, 0x05,
     229,  224,   16,   16, 0x05,
     252,  224,   16,   16, 0x05,
     283,  275,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     316,   16,   16,   16, 0x0a,
     326,   16,   16,   16, 0x0a,
     336,   16,   16,   16, 0x0a,
     354,   16,   16,   16, 0x0a,
     376,   16,   16,   16, 0x0a,
     407,   16,   16,   16, 0x0a,
     430,   16,   16,   16, 0x0a,
     459,   16,  447,   16, 0x0a,
     473,   42,   16,   16, 0x0a,
     501,   16,  447,   16, 0x0a,
     508,   80,   16,   16, 0x0a,
     529,   16,   16,   16, 0x0a,
     553,  545,   16,   16, 0x0a,
     588,   16,   16,   16, 0x0a,
     624,  621,   16,   16, 0x0a,
     736,   16,  706,   16, 0x0a,
     754,   16,   16,   16, 0x0a,
     768,   16,   16,   16, 0x0a,
     793,   16,   16,   16, 0x0a,
     817,   16,   16,   16, 0x0a,

 // methods: signature, parameters, type, tag, flags
     847,  837,   16,   16, 0x02,
     870,   16,   16,   16, 0x02,
     888,   16,   16,   16, 0x02,
     918,  916,  908,   16, 0x02,
     947,  916,   16,   16, 0x02,
    1006,  977,   16,   16, 0x02,
    1069,   16, 1049,   16, 0x02,
    1089,   16,   16,   16, 0x02,
    1122,   16,   16,   16, 0x02,
    1139,   16,   16,   16, 0x02,

 // properties: name, type, flags
    1156,  447, 0x0b495103,
      80,  447, 0x0b495103,
    1168,  706, 0x00095009,
    1189, 1184, 0x01095103,

 // properties: notify_signal_id
       1,
       2,
       0,
       0,

       0        // eod
};

static const char qt_meta_stringdata_FriendtrackerUI[] = {
    "FriendtrackerUI\0\0userProfileInitialized()\0"
    "ppIds\0onlinePpIdsChanged(QStringList)\0"
    "pins\0pinsChanged(QStringList)\0"
    "updateProfilePictureOnMap(bb::cascades::Image)\0"
    "ppId,\0"
    "updateFriendProfilePictureOnMap(QString,bb::cascades::Image)\0"
    "ppId\0showPinSignal(QString)\0"
    "hidePinSignal(QString)\0lat,lng\0"
    "myLocationUpdated(double,double)\0"
    "initMap()\0loadMap()\0initUserProfile()\0"
    "login(QGeoCoordinate)\0"
    "updateLocation(QGeoCoordinate)\0"
    "setSessionKey(QString)\0endApplication()\0"
    "QStringList\0onlinePpIds()\0"
    "setOnlinePpIds(QStringList)\0pins()\0"
    "setPins(QStringList)\0pullLocations()\0"
    "friends\0updateFriendsLocation(QList<User>)\0"
    "updateProfilePicture(QByteArray)\0,,\0"
    "returnFriendDisplayPicture(QString,bb::platform::bbm::ImageType::Type,"
    "QByteArray)\0"
    "bb::cascades::GroupDataModel*\0"
    "friendListModel()\0updatePpIds()\0"
    "changeToFullScreenMode()\0"
    "changeToThumbnailMode()\0changeToInvisible()\0"
    "frequency\0setRegularMode(double)\0"
    "setRealtimeMode()\0setVisibility(bool)\0"
    "QString\0,\0getValueFor(QString,QString)\0"
    "saveValueFor(QString,QString)\0"
    "containerObject,x,y,property\0"
    "getAddress(QObject*,double,double,QString)\0"
    "bb::cascades::Image\0getProfilePicture()\0"
    "askFriendProfilePicture(QString)\0"
    "showPin(QString)\0hidePin(QString)\0"
    "onlinePpIds\0friendListModel\0bool\0"
    "initial\0"
};

void FriendtrackerUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FriendtrackerUI *_t = static_cast<FriendtrackerUI *>(_o);
        switch (_id) {
        case 0: _t->userProfileInitialized(); break;
        case 1: _t->onlinePpIdsChanged((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 2: _t->pinsChanged((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 3: _t->updateProfilePictureOnMap((*reinterpret_cast< const bb::cascades::Image(*)>(_a[1]))); break;
        case 4: _t->updateFriendProfilePictureOnMap((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const bb::cascades::Image(*)>(_a[2]))); break;
        case 5: _t->showPinSignal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->hidePinSignal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->myLocationUpdated((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: _t->initMap(); break;
        case 9: _t->loadMap(); break;
        case 10: _t->initUserProfile(); break;
        case 11: _t->login((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 12: _t->updateLocation((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 13: _t->setSessionKey((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->endApplication(); break;
        case 15: { QStringList _r = _t->onlinePpIds();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 16: _t->setOnlinePpIds((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 17: { QStringList _r = _t->pins();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 18: _t->setPins((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 19: _t->pullLocations(); break;
        case 20: _t->updateFriendsLocation((*reinterpret_cast< const QList<User>(*)>(_a[1]))); break;
        case 21: _t->updateProfilePicture((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 22: _t->returnFriendDisplayPicture((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const bb::platform::bbm::ImageType::Type(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3]))); break;
        case 23: { bb::cascades::GroupDataModel* _r = _t->friendListModel();
            if (_a[0]) *reinterpret_cast< bb::cascades::GroupDataModel**>(_a[0]) = _r; }  break;
        case 24: _t->updatePpIds(); break;
        case 25: _t->changeToFullScreenMode(); break;
        case 26: _t->changeToThumbnailMode(); break;
        case 27: _t->changeToInvisible(); break;
        case 28: _t->setRegularMode((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->setRealtimeMode(); break;
        case 30: _t->setVisibility((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: { QString _r = _t->getValueFor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 32: _t->saveValueFor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 33: _t->getAddress((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 34: { bb::cascades::Image _r = _t->getProfilePicture();
            if (_a[0]) *reinterpret_cast< bb::cascades::Image*>(_a[0]) = _r; }  break;
        case 35: _t->askFriendProfilePicture((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 36: _t->showPin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 37: _t->hidePin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FriendtrackerUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FriendtrackerUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FriendtrackerUI,
      qt_meta_data_FriendtrackerUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FriendtrackerUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FriendtrackerUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FriendtrackerUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FriendtrackerUI))
        return static_cast<void*>(const_cast< FriendtrackerUI*>(this));
    return QObject::qt_metacast(_clname);
}

int FriendtrackerUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QStringList*>(_v) = onlinePpIds(); break;
        case 1: *reinterpret_cast< QStringList*>(_v) = pins(); break;
        case 2: *reinterpret_cast< bb::cascades::GroupDataModel**>(_v) = friendListModel(); break;
        case 3: *reinterpret_cast< bool*>(_v) = getInitial(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setOnlinePpIds(*reinterpret_cast< QStringList*>(_v)); break;
        case 1: setPins(*reinterpret_cast< QStringList*>(_v)); break;
        case 3: setInitial(*reinterpret_cast< bool*>(_v)); break;
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
void FriendtrackerUI::userProfileInitialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FriendtrackerUI::onlinePpIdsChanged(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FriendtrackerUI::pinsChanged(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FriendtrackerUI::updateProfilePictureOnMap(const bb::cascades::Image & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FriendtrackerUI::updateFriendProfilePictureOnMap(const QString & _t1, const bb::cascades::Image & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FriendtrackerUI::showPinSignal(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FriendtrackerUI::hidePinSignal(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FriendtrackerUI::myLocationUpdated(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
