/****************************************************************************
** Meta object code from reading C++ file 'MadPix.h'
**
** Created: Fri 26. Jun 20:22:48 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MadPix.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MadPix.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MadPix[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      15,    8,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,    7,    7,    7, 0x0a,
      39,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MadPix[] = {
    "MadPix\0\0pixmap\0sendPix(QPixmap)\0grab()\0"
    "preparePixmap(QPixmap)\0"
};

const QMetaObject MadPix::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MadPix,
      qt_meta_data_MadPix, 0 }
};

const QMetaObject *MadPix::metaObject() const
{
    return &staticMetaObject;
}

void *MadPix::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MadPix))
        return static_cast<void*>(const_cast< MadPix*>(this));
    return QThread::qt_metacast(_clname);
}

int MadPix::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendPix((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 1: grab(); break;
        case 2: preparePixmap((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MadPix::sendPix(QPixmap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
