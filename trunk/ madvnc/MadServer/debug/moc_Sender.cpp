/****************************************************************************
** Meta object code from reading C++ file 'Sender.h'
**
** Created: Fri 19. Jun 18:59:48 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Sender.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Sender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Sender[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_Sender[] = {
    "Sender\0"
};

const QMetaObject Sender::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_Sender,
      qt_meta_data_Sender, 0 }
};

const QMetaObject *Sender::metaObject() const
{
    return &staticMetaObject;
}

void *Sender::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Sender))
        return static_cast<void*>(const_cast< Sender*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int Sender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ClientSocket[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_ClientSocket[] = {
    "ClientSocket\0"
};

const QMetaObject ClientSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_ClientSocket,
      qt_meta_data_ClientSocket, 0 }
};

const QMetaObject *ClientSocket::metaObject() const
{
    return &staticMetaObject;
}

void *ClientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientSocket))
        return static_cast<void*>(const_cast< ClientSocket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int ClientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
