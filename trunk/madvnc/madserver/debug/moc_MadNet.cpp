/****************************************************************************
** Meta object code from reading C++ file 'MadNet.h'
**
** Created: Tue 1. Sep 19:31:31 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MadNet.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MadNet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MadNet[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,    7,    7,    7, 0x0a,
      42,    7,    7,    7, 0x0a,
      66,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MadNet[] = {
    "MadNet\0\0connectionStart()\0prepareClient()\0"
    "sendBuffer(QByteArray*)\0bytesWrite(qint64)\0"
};

const QMetaObject MadNet::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MadNet,
      qt_meta_data_MadNet, 0 }
};

const QMetaObject *MadNet::metaObject() const
{
    return &staticMetaObject;
}

void *MadNet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MadNet))
        return static_cast<void*>(const_cast< MadNet*>(this));
    return QThread::qt_metacast(_clname);
}

int MadNet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connectionStart(); break;
        case 1: prepareClient(); break;
        case 2: sendBuffer((*reinterpret_cast< QByteArray*(*)>(_a[1]))); break;
        case 3: bytesWrite((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MadNet::connectionStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
