/****************************************************************************
** Meta object code from reading C++ file 'file_ui.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/file_ui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'file_ui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_file_ui[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      22,    8,    8,    8, 0x05,
      43,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,    8,    8,    8, 0x08,
      61,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_file_ui[] = {
    "file_ui\0\0showDialog()\0appendToLog(QString)\0"
    "finished()\0save()\0clearInputText()\0"
};

void file_ui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        file_ui *_t = static_cast<file_ui *>(_o);
        switch (_id) {
        case 0: _t->showDialog(); break;
        case 1: _t->appendToLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->finished(); break;
        case 3: _t->save(); break;
        case 4: _t->clearInputText(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData file_ui::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject file_ui::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_file_ui,
      qt_meta_data_file_ui, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &file_ui::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *file_ui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *file_ui::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_file_ui))
        return static_cast<void*>(const_cast< file_ui*>(this));
    return QObject::qt_metacast(_clname);
}

int file_ui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void file_ui::showDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void file_ui::appendToLog(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void file_ui::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
