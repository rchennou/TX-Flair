/****************************************************************************
** Meta object code from reading C++ file 'Map.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Map.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Map.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Map[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,    5,    4,    4, 0x08,
      30,    5,    4,    4, 0x08,
      49,    5,    4,    4, 0x08,
      72,   66,    4,    4, 0x08,
      90,    4,    4,    4, 0x08,
      99,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Map[] = {
    "Map\0\0index\0changeMapType(int)\0"
    "selectService(int)\0changeproxy(int)\0"
    "value\0updateZoom(qreal)\0zoomIn()\0"
    "zoomOut()\0"
};

void Map::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Map *_t = static_cast<Map *>(_o);
        switch (_id) {
        case 0: _t->changeMapType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->selectService((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changeproxy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateZoom((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 4: _t->zoomIn(); break;
        case 5: _t->zoomOut(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Map::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Map::staticMetaObject = {
    { &DataRemote::staticMetaObject, qt_meta_stringdata_Map,
      qt_meta_data_Map, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Map::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Map::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Map::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Map))
        return static_cast<void*>(const_cast< Map*>(this));
    return DataRemote::qt_metacast(_clname);
}

int Map::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DataRemote::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
