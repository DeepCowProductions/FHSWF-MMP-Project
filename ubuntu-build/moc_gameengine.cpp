/****************************************************************************
** Meta object code from reading C++ file 'gameengine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/game/gameengine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameEngine_t {
    QByteArrayData data[7];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameEngine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameEngine_t qt_meta_stringdata_GameEngine = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameEngine"
QT_MOC_LITERAL(1, 11, 19), // "shootWithPlayerShip"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 11), // "spawnBullet"
QT_MOC_LITERAL(4, 44, 8), // "location"
QT_MOC_LITERAL(5, 53, 9), // "direction"
QT_MOC_LITERAL(6, 63, 8) // "velocity"

    },
    "GameEngine\0shootWithPlayerShip\0\0"
    "spawnBullet\0location\0direction\0velocity"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameEngine[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    3,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QVector3D, QMetaType::Double,    4,    5,    6,

       0        // eod
};

void GameEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameEngine *_t = static_cast<GameEngine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->shootWithPlayerShip(); break;
        case 1: _t->spawnBullet((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QVector3D(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject GameEngine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GameEngine.data,
      qt_meta_data_GameEngine,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GameEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GameEngine.stringdata0))
        return static_cast<void*>(const_cast< GameEngine*>(this));
    return QObject::qt_metacast(_clname);
}

int GameEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
