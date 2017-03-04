/****************************************************************************
** Meta object code from reading C++ file 'DataPlot2D.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/DataPlot2D.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DataPlot2D.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DataPlot2D[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   12,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DataPlot2D[] = {
    "DataPlot2D\0\0itemInfo,on\0"
    "legendChecked(QVariant,bool)\0"
};

void DataPlot2D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataPlot2D *_t = static_cast<DataPlot2D *>(_o);
        switch (_id) {
        case 0: _t->legendChecked((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DataPlot2D::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataPlot2D::staticMetaObject = {
    { &DataRemote::staticMetaObject, qt_meta_stringdata_DataPlot2D,
      qt_meta_data_DataPlot2D, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataPlot2D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataPlot2D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataPlot2D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataPlot2D))
        return static_cast<void*>(const_cast< DataPlot2D*>(this));
    return DataRemote::qt_metacast(_clname);
}

int DataPlot2D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DataRemote::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
