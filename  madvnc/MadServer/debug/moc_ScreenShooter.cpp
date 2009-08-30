/****************************************************************************
** Meta object code from reading C++ file 'ScreenShooter.h'
**
** Created: Fri 26. Jun 20:22:46 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ScreenShooter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScreenShooter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScreenShoter[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ScreenShoter[] = {
    "ScreenShoter\0\0newPixmap(QPixmap)\0"
    "makeScreenShot()\0"
};

const QMetaObject ScreenShoter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScreenShoter,
      qt_meta_data_ScreenShoter, 0 }
};

const QMetaObject *ScreenShoter::metaObject() const
{
    return &staticMetaObject;
}

void *ScreenShoter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenShoter))
        return static_cast<void*>(const_cast< ScreenShoter*>(this));
    return QObject::qt_metacast(_clname);
}

int ScreenShoter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newPixmap((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 1: makeScreenShot(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ScreenShoter::newPixmap(QPixmap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
