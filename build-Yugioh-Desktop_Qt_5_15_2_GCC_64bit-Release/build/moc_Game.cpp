/****************************************************************************
** Meta object code from reading C++ file 'Game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Yugioh/headers/Game.h"
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
struct qt_meta_stringdata_Game_t {
    QByteArrayData data[23];
    char stringdata0[341];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Game_t qt_meta_stringdata_Game = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Game"
QT_MOC_LITERAL(1, 5, 17), // "mainWindowResized"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "QResizeEvent*"
QT_MOC_LITERAL(4, 38, 16), // "gamePhaseChanged"
QT_MOC_LITERAL(5, 55, 14), // "GamePhasesEnum"
QT_MOC_LITERAL(6, 70, 12), // "newGamePhase"
QT_MOC_LITERAL(7, 83, 9), // "turnEnded"
QT_MOC_LITERAL(8, 93, 16), // "cardAddedToScene"
QT_MOC_LITERAL(9, 110, 5), // "Card*"
QT_MOC_LITERAL(10, 116, 24), // "onBattlePhaseButtonClick"
QT_MOC_LITERAL(11, 141, 23), // "onMainPhase2ButtonClick"
QT_MOC_LITERAL(12, 165, 21), // "onEndPhaseButtonClick"
QT_MOC_LITERAL(13, 187, 18), // "onMainWindowResize"
QT_MOC_LITERAL(14, 206, 17), // "onGamePhaseChange"
QT_MOC_LITERAL(15, 224, 9), // "onTurnEnd"
QT_MOC_LITERAL(16, 234, 18), // "onCardAddedToScene"
QT_MOC_LITERAL(17, 253, 11), // "const Card*"
QT_MOC_LITERAL(18, 265, 11), // "onCardHover"
QT_MOC_LITERAL(19, 277, 21), // "onActivateButtonClick"
QT_MOC_LITERAL(20, 299, 4), // "Card"
QT_MOC_LITERAL(21, 304, 16), // "onSetButtonClick"
QT_MOC_LITERAL(22, 321, 19) // "onSummonButtonClick"

    },
    "Game\0mainWindowResized\0\0QResizeEvent*\0"
    "gamePhaseChanged\0GamePhasesEnum\0"
    "newGamePhase\0turnEnded\0cardAddedToScene\0"
    "Card*\0onBattlePhaseButtonClick\0"
    "onMainPhase2ButtonClick\0onEndPhaseButtonClick\0"
    "onMainWindowResize\0onGamePhaseChange\0"
    "onTurnEnd\0onCardAddedToScene\0const Card*\0"
    "onCardHover\0onActivateButtonClick\0"
    "Card\0onSetButtonClick\0onSummonButtonClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Game[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,
       7,    0,   95,    2, 0x06 /* Public */,
       8,    1,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   99,    2, 0x08 /* Private */,
      11,    0,  100,    2, 0x08 /* Private */,
      12,    0,  101,    2, 0x08 /* Private */,
      13,    1,  102,    2, 0x08 /* Private */,
      14,    1,  105,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    1,  109,    2, 0x08 /* Private */,
      18,    1,  112,    2, 0x08 /* Private */,
      19,    1,  115,    2, 0x08 /* Private */,
      21,    1,  118,    2, 0x08 /* Private */,
      22,    1,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 20,    2,
    QMetaType::Void, 0x80000000 | 20,    2,
    QMetaType::Void, 0x80000000 | 20,    2,

       0        // eod
};

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Game *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mainWindowResized((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 1: _t->gamePhaseChanged((*reinterpret_cast< const GamePhasesEnum(*)>(_a[1]))); break;
        case 2: _t->turnEnded(); break;
        case 3: _t->cardAddedToScene((*reinterpret_cast< Card*(*)>(_a[1]))); break;
        case 4: _t->onBattlePhaseButtonClick(); break;
        case 5: _t->onMainPhase2ButtonClick(); break;
        case 6: _t->onEndPhaseButtonClick(); break;
        case 7: _t->onMainWindowResize((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 8: _t->onGamePhaseChange((*reinterpret_cast< const GamePhasesEnum(*)>(_a[1]))); break;
        case 9: _t->onTurnEnd(); break;
        case 10: _t->onCardAddedToScene((*reinterpret_cast< const Card*(*)>(_a[1]))); break;
        case 11: _t->onCardHover((*reinterpret_cast< Card*(*)>(_a[1]))); break;
        case 12: _t->onActivateButtonClick((*reinterpret_cast< const Card(*)>(_a[1]))); break;
        case 13: _t->onSetButtonClick((*reinterpret_cast< const Card(*)>(_a[1]))); break;
        case 14: _t->onSummonButtonClick((*reinterpret_cast< const Card(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Game::*)(QResizeEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::mainWindowResized)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Game::*)(const GamePhasesEnum & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::gamePhaseChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Game::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::turnEnded)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Game::*)(Card * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Game::cardAddedToScene)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Game::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Game.data,
    qt_meta_data_Game,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Game.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Game::mainWindowResized(QResizeEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Game::gamePhaseChanged(const GamePhasesEnum & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Game::turnEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Game::cardAddedToScene(Card * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
