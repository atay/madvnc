/****************************************************************************
** Meta object code from reading C++ file 'MadShooter.h'
**
** Created: Tue 1. Sep 19:31:37 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MadShooter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MadShooter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MadShooter[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MadShooter[] = {
    "MadShooter\0\0sendBuffer(QByteArray*)\0"
    "makeScreenShot()\0"
};

const QMetaObject MadShooter::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MadShooter,
      qt_meta_data_MadShooter, 0 }
};

const QMetaObject *MadShooter::metaObject() const
{
    return &staticMetaObject;
}

void *MadShooter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MadShooter))
        return static_cast<void*>(const_cast< MadShooter*>(this));
    return QThread::qt_metacast(_clname);
}

int MadShooter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendBuffer((*reinterpret_cast< QByteArray*(*)>(_a[1]))); break;
        case 1: makeScreenShot(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MadShooter::sendBuffer(QByteArray * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
