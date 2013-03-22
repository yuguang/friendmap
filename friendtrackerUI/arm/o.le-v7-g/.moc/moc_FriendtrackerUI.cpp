/****************************************************************************
** Meta object code from reading C++ file 'FriendtrackerUI.hpp'
**
** Created: Fri Mar 22 13:55:09 2013
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
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   16,   16,   16, 0x0a,
      56,   16,   16,   16, 0x0a,
      74,   16,   16,   16, 0x0a,
      96,   16,   16,   16, 0x0a,
     127,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FriendtrackerUI[] = {
    "FriendtrackerUI\0\0userProfileInitialized()\0"
    "initWebMaps()\0initUserProfile()\0"
    "login(QGeoCoordinate)\0"
    "updateLocation(QGeoCoordinate)\0"
    "setSessionKey(QString)\0"
};

void FriendtrackerUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FriendtrackerUI *_t = static_cast<FriendtrackerUI *>(_o);
        switch (_id) {
        case 0: _t->userProfileInitialized(); break;
        case 1: _t->initWebMaps(); break;
        case 2: _t->initUserProfile(); break;
        case 3: _t->login((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 4: _t->updateLocation((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 5: _t->setSessionKey((*reinterpret_cast< const QString(*)>(_a[1]))); break;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FriendtrackerUI::userProfileInitialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
