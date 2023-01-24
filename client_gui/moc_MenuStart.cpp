/****************************************************************************
** Meta object code from reading C++ file 'MenuStart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/MenuStart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MenuStart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MenuStart_t {
    QByteArrayData data[10];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MenuStart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MenuStart_t qt_meta_stringdata_MenuStart = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MenuStart"
QT_MOC_LITERAL(1, 10, 16), // "showMenuNotLogin"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "showCredit"
QT_MOC_LITERAL(4, 39, 9), // "showGuide"
QT_MOC_LITERAL(5, 49, 4), // "quit"
QT_MOC_LITERAL(6, 54, 19), // "on_startBtn_clicked"
QT_MOC_LITERAL(7, 74, 19), // "on_guideBtn_clicked"
QT_MOC_LITERAL(8, 94, 20), // "on_creditBtn_clicked"
QT_MOC_LITERAL(9, 115, 18) // "on_quitBtn_clicked"

    },
    "MenuStart\0showMenuNotLogin\0\0showCredit\0"
    "showGuide\0quit\0on_startBtn_clicked\0"
    "on_guideBtn_clicked\0on_creditBtn_clicked\0"
    "on_quitBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuStart[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MenuStart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MenuStart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showMenuNotLogin(); break;
        case 1: _t->showCredit(); break;
        case 2: _t->showGuide(); break;
        case 3: _t->quit(); break;
        case 4: _t->on_startBtn_clicked(); break;
        case 5: _t->on_guideBtn_clicked(); break;
        case 6: _t->on_creditBtn_clicked(); break;
        case 7: _t->on_quitBtn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MenuStart::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuStart::showMenuNotLogin)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MenuStart::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuStart::showCredit)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MenuStart::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuStart::showGuide)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MenuStart::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuStart::quit)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MenuStart::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MenuStart.data,
    qt_meta_data_MenuStart,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MenuStart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuStart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MenuStart.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MenuStart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MenuStart::showMenuNotLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MenuStart::showCredit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MenuStart::showGuide()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MenuStart::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
