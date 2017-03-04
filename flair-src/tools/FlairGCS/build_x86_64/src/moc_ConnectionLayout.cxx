/****************************************************************************
** Meta object code from reading C++ file 'ConnectionLayout.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/ConnectionLayout.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConnectionLayout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConnectionLayout[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   18,   17,   17, 0x05,
      53,   46,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   75,   17,   17, 0x08,
     103,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ConnectionLayout[] = {
    "ConnectionLayout\0\0name\0setRemoteName(QString)\0"
    "rxRate\0computedRxRate(float)\0buf,size\0"
    "receive(char*,int)\0computeRxRate()\0"
};

void ConnectionLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConnectionLayout *_t = static_cast<ConnectionLayout *>(_o);
        switch (_id) {
        case 0: _t->setRemoteName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->computedRxRate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->receive((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->computeRxRate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConnectionLayout::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConnectionLayout::staticMetaObject = {
    { &Layout::staticMetaObject, qt_meta_stringdata_ConnectionLayout,
      qt_meta_data_ConnectionLayout, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConnectionLayout::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConnectionLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConnectionLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionLayout))
        return static_cast<void*>(const_cast< ConnectionLayout*>(this));
    return Layout::qt_metacast(_clname);
}

int ConnectionLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Layout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ConnectionLayout::setRemoteName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConnectionLayout::computedRxRate(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
