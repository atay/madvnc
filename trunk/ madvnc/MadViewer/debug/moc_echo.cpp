/****************************************************************************
** Meta object code from reading C++ file 'echo.h'
**
** Created: Sat 20. Jun 21:34:45 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../echo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'echo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Echo[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      24,    5,    5,    5, 0x0a,
      40,    5,    5,    5, 0x0a,
      53,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Echo[] = {
    "Echo\0\0startConnection()\0prepareClient()\0"
    "sendWindow()\0drawWindow()\0"
};

const QMetaObject Echo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Echo,
      qt_meta_data_Echo, 0 }
};

const QMetaObject *Echo::metaObject() const
{
    return &staticMetaObject;
}

void *Echo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Echo))
        return static_cast<void*>(const_cast< Echo*>(this));
    return QDialog::qt_metacast(_clname);
}

int Echo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: startConnection(); break;
        case 1: prepareClient(); break;
        case 2: sendWindow(); break;
        case 3: drawWindow(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
