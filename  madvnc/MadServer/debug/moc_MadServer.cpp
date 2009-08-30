/****************************************************************************
** Meta object code from reading C++ file 'MadServer.h'
**
** Created: Fri 26. Jun 20:10:34 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MadServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MadServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MadServer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   10,   10,   10, 0x0a,
      50,   45,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MadServer[] = {
    "MadServer\0\0connectionStart()\0"
    "prepareClient()\0qpix\0sendWindow(QPixmap)\0"
};

const QMetaObject MadServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_MadServer,
      qt_meta_data_MadServer, 0 }
};

const QMetaObject *MadServer::metaObject() const
{
    return &staticMetaObject;
}

void *MadServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MadServer))
        return static_cast<void*>(const_cast< MadServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int MadServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connectionStart(); break;
        case 1: prepareClient(); break;
        case 2: sendWindow((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MadServer::connectionStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
