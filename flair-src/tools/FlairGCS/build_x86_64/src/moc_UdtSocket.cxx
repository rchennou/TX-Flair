/****************************************************************************
** Meta object code from reading C++ file 'UdtSocket.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/UdtSocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UdtSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UdtSocket[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   10,   10,   10, 0x0a,
      58,   10,   10,   10, 0x0a,
      74,   65,   10,   10, 0x0a,
     100,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UdtSocket[] = {
    "UdtSocket\0\0,size\0dataReady(char*,int)\0"
    "handleConnections()\0kill()\0buf,size\0"
    "write(const char*,qint64)\0heartbeat()\0"
};

void UdtSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UdtSocket *_t = static_cast<UdtSocket *>(_o);
        switch (_id) {
        case 0: _t->dataReady((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->handleConnections(); break;
        case 2: _t->kill(); break;
        case 3: _t->write((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->heartbeat(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UdtSocket::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UdtSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UdtSocket,
      qt_meta_data_UdtSocket, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UdtSocket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UdtSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UdtSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UdtSocket))
        return static_cast<void*>(const_cast< UdtSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int UdtSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void UdtSocket::dataReady(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
