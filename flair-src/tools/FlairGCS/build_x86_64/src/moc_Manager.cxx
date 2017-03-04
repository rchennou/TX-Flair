/****************************************************************************
** Meta object code from reading C++ file 'Manager.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Manager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Manager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,    8,    8,    8, 0x08,
      46,    8,    8,    8, 0x08,
      53,    8,    8,    8, 0x08,
      60,    8,    8,    8, 0x08,
      67,    8,    8,    8, 0x08,
      79,   75,    8,    8, 0x08,
     111,  105,    8,    8, 0x08,
     142,  137,    8,    8, 0x08,
     166,  159,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Manager[] = {
    "Manager\0\0killUdtSockets()\0acceptConnections()\0"
    "load()\0send()\0save()\0reset()\0obj\0"
    "layoutDestroyed(QObject*)\0index\0"
    "tabBarCurrentChanged(int)\0name\0"
    "tabName(QString)\0rxRate\0printRxRates(float)\0"
};

void Manager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Manager *_t = static_cast<Manager *>(_o);
        switch (_id) {
        case 0: _t->killUdtSockets(); break;
        case 1: _t->acceptConnections(); break;
        case 2: _t->load(); break;
        case 3: _t->send(); break;
        case 4: _t->save(); break;
        case 5: _t->reset(); break;
        case 6: _t->layoutDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 7: _t->tabBarCurrentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->tabName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->printRxRates((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Manager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Manager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Manager,
      qt_meta_data_Manager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Manager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Manager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Manager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Manager))
        return static_cast<void*>(const_cast< Manager*>(this));
    return QWidget::qt_metacast(_clname);
}

int Manager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Manager::killUdtSockets()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
