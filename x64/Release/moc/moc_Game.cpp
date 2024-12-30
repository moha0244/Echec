/****************************************************************************
** Meta object code from reading C++ file 'Game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Game.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_modele__Game_t {
    QByteArrayData data[18];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_modele__Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_modele__Game_t qt_meta_stringdata_modele__Game = {
    {
QT_MOC_LITERAL(0, 0, 12), // "modele::Game"
QT_MOC_LITERAL(1, 13, 10), // "pieceBouge"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "Piece*"
QT_MOC_LITERAL(4, 32, 5), // "piece"
QT_MOC_LITERAL(5, 38, 10), // "playerMove"
QT_MOC_LITERAL(6, 49, 6), // "Player"
QT_MOC_LITERAL(7, 56, 6), // "player"
QT_MOC_LITERAL(8, 63, 6), // "Board&"
QT_MOC_LITERAL(9, 70, 5), // "board"
QT_MOC_LITERAL(10, 76, 5), // "Spot*"
QT_MOC_LITERAL(11, 82, 5), // "start"
QT_MOC_LITERAL(12, 88, 3), // "end"
QT_MOC_LITERAL(13, 92, 8), // "movecase"
QT_MOC_LITERAL(14, 101, 2), // "i_"
QT_MOC_LITERAL(15, 104, 2), // "j_"
QT_MOC_LITERAL(16, 107, 1), // "i"
QT_MOC_LITERAL(17, 109, 1) // "j"

    },
    "modele::Game\0pieceBouge\0\0Piece*\0piece\0"
    "playerMove\0Player\0player\0Board&\0board\0"
    "Spot*\0start\0end\0movecase\0i_\0j_\0i\0j"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_modele__Game[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    4,   32,    2, 0x0a /* Public */,
      13,    5,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8, 0x80000000 | 10, 0x80000000 | 10,    7,    9,   11,   12,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   14,   15,   16,   17,

       0        // eod
};

void modele::Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Game *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pieceBouge((*reinterpret_cast< Piece*(*)>(_a[1]))); break;
        case 1: _t->playerMove((*reinterpret_cast< Player(*)>(_a[1])),(*reinterpret_cast< Board(*)>(_a[2])),(*reinterpret_cast< Spot*(*)>(_a[3])),(*reinterpret_cast< Spot*(*)>(_a[4]))); break;
        case 2: _t->movecase((*reinterpret_cast< Board(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Game::*)(Piece * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::pieceBouge)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject modele::Game::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_modele__Game.data,
    qt_meta_data_modele__Game,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *modele::Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *modele::Game::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_modele__Game.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int modele::Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void modele::Game::pieceBouge(Piece * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
