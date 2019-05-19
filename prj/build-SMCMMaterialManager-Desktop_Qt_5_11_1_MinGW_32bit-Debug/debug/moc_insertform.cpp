/****************************************************************************
** Meta object code from reading C++ file 'insertform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/SMCMMaterialManager/InsertForm/insertform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'insertform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cls_insert_form_t {
    QByteArrayData data[7];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cls_insert_form_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cls_insert_form_t qt_meta_stringdata_cls_insert_form = {
    {
QT_MOC_LITERAL(0, 0, 15), // "cls_insert_form"
QT_MOC_LITERAL(1, 16, 19), // "needUpdateTableView"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 6), // "closed"
QT_MOC_LITERAL(4, 44, 17), // "elementIsSelected"
QT_MOC_LITERAL(5, 62, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(6, 79, 10) // "insertData"

    },
    "cls_insert_form\0needUpdateTableView\0"
    "\0closed\0elementIsSelected\0QListWidgetItem*\0"
    "insertData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cls_insert_form[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   36,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,

       0        // eod
};

void cls_insert_form::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        cls_insert_form *_t = static_cast<cls_insert_form *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->needUpdateTableView(); break;
        case 1: _t->closed(); break;
        case 2: _t->elementIsSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->insertData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (cls_insert_form::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cls_insert_form::needUpdateTableView)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (cls_insert_form::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cls_insert_form::closed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject cls_insert_form::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_cls_insert_form.data,
      qt_meta_data_cls_insert_form,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *cls_insert_form::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cls_insert_form::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cls_insert_form.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int cls_insert_form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void cls_insert_form::needUpdateTableView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void cls_insert_form::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
