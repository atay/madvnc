/****************************************************************************
** Meta object code from reading C++ file 'MadSocket.h'
**
** Created: Tue 1. Sep 19:43:59 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MadSocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MadSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MadSocket[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      29,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MadSocket[] = {
    "MadSocket\0\0startConnection()\0drawWindow()\0"
};

const QMetaObject MadSocket::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MadSocket,
      qt_meta_data_MadSocket, 0 }
};

const QMetaObject *MadSocket::metaObject() const
{
    return &staticMetaObject;
}

void *MadSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MadSocket))
        return static_cast<void*>(const_cast< MadSocket*>(this));
    return QDialog::qt_metacast(_clname);
}

int MadSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: startConnection(); break;
        case 1: drawWindow(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
