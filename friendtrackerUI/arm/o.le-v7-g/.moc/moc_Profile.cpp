/****************************************************************************
** Meta object code from reading C++ file 'Profile.hpp'
**
** Created: Sat Mar 23 16:32:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Profile.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Profile.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Profile[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       9,   29, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,    8,    8,    8, 0x0a,
      33,    8,    8,    8, 0x0a,

 // properties: name, type, flags
      62,   57, 0x01495001,
      75,   67, 0x0a495001,
      87,   67, 0x0a495001,
     101,   67, 0x0a495001,
     117,   67, 0x0a495001,
     122,   67, 0x0a495001,
     133,   67, 0x0a495001,
     140,   67, 0x0a495001,
     165,  156, 0xff495001,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,

       0        // eod
};

static const char qt_meta_stringdata_Profile[] = {
    "Profile\0\0profileChanged()\0show()\0"
    "requestDisplayPicture()\0bool\0busy\0"
    "QString\0displayName\0statusMessage\0"
    "personalMessage\0ppid\0appVersion\0handle\0"
    "platformVersion\0QVariant\0displayPicture\0"
};

void Profile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Profile *_t = static_cast<Profile *>(_o);
        switch (_id) {
        case 0: _t->profileChanged(); break;
        case 1: _t->show(); break;
        case 2: _t->requestDisplayPicture(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Profile::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Profile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Profile,
      qt_meta_data_Profile, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Profile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Profile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Profile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Profile))
        return static_cast<void*>(const_cast< Profile*>(this));
    return QObject::qt_metacast(_clname);
}

int Profile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = busy(); break;
        case 1: *reinterpret_cast< QString*>(_v) = displayName(); break;
        case 2: *reinterpret_cast< QString*>(_v) = statusMessage(); break;
        case 3: *reinterpret_cast< QString*>(_v) = personalMessage(); break;
        case 4: *reinterpret_cast< QString*>(_v) = ppid(); break;
        case 5: *reinterpret_cast< QString*>(_v) = appVersion(); break;
        case 6: *reinterpret_cast< QString*>(_v) = handle(); break;
        case 7: *reinterpret_cast< QString*>(_v) = platformVersion(); break;
        case 8: *reinterpret_cast< QVariant*>(_v) = displayPicture(); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Profile::profileChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
