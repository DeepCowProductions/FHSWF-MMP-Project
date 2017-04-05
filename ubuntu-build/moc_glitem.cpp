/****************************************************************************
** Meta object code from reading C++ file 'glitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/glcore/glitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GLItem_t {
    QByteArrayData data[32];
    char stringdata0[481];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLItem_t qt_meta_stringdata_GLItem = {
    {
QT_MOC_LITERAL(0, 0, 6), // "GLItem"
QT_MOC_LITERAL(1, 7, 27), // "vertexShaderFilenameChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 3), // "arg"
QT_MOC_LITERAL(4, 40, 29), // "fragmentShaderFilenameChanged"
QT_MOC_LITERAL(5, 70, 24), // "movementActivatedChanged"
QT_MOC_LITERAL(6, 95, 16), // "viewportXChanged"
QT_MOC_LITERAL(7, 112, 16), // "viewportYChanged"
QT_MOC_LITERAL(8, 129, 11), // "paintBefore"
QT_MOC_LITERAL(9, 141, 10), // "paintAfter"
QT_MOC_LITERAL(10, 152, 10), // "toggleMove"
QT_MOC_LITERAL(11, 163, 12), // "mousePressed"
QT_MOC_LITERAL(12, 176, 1), // "x"
QT_MOC_LITERAL(13, 178, 1), // "y"
QT_MOC_LITERAL(14, 180, 20), // "mousePositionChanged"
QT_MOC_LITERAL(15, 201, 13), // "mouseReleased"
QT_MOC_LITERAL(16, 215, 23), // "setVertexShaderFilename"
QT_MOC_LITERAL(17, 239, 25), // "setFragmentShaderFilename"
QT_MOC_LITERAL(18, 265, 12), // "setViewportX"
QT_MOC_LITERAL(19, 278, 12), // "setViewportY"
QT_MOC_LITERAL(20, 291, 20), // "setMovementActivated"
QT_MOC_LITERAL(21, 312, 17), // "movementActivated"
QT_MOC_LITERAL(22, 330, 19), // "handleWindowChanged"
QT_MOC_LITERAL(23, 350, 13), // "QQuickWindow*"
QT_MOC_LITERAL(24, 364, 3), // "win"
QT_MOC_LITERAL(25, 368, 14), // "onTimerTimeout"
QT_MOC_LITERAL(26, 383, 18), // "synchronizeThreads"
QT_MOC_LITERAL(27, 402, 14), // "deleteRenderer"
QT_MOC_LITERAL(28, 417, 20), // "vertexShaderFilename"
QT_MOC_LITERAL(29, 438, 22), // "fragmentShaderFilename"
QT_MOC_LITERAL(30, 461, 9), // "viewportX"
QT_MOC_LITERAL(31, 471, 9) // "viewportY"

    },
    "GLItem\0vertexShaderFilenameChanged\0\0"
    "arg\0fragmentShaderFilenameChanged\0"
    "movementActivatedChanged\0viewportXChanged\0"
    "viewportYChanged\0paintBefore\0paintAfter\0"
    "toggleMove\0mousePressed\0x\0y\0"
    "mousePositionChanged\0mouseReleased\0"
    "setVertexShaderFilename\0"
    "setFragmentShaderFilename\0setViewportX\0"
    "setViewportY\0setMovementActivated\0"
    "movementActivated\0handleWindowChanged\0"
    "QQuickWindow*\0win\0onTimerTimeout\0"
    "synchronizeThreads\0deleteRenderer\0"
    "vertexShaderFilename\0fragmentShaderFilename\0"
    "viewportX\0viewportY"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       5,  168, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  114,    2, 0x06 /* Public */,
       4,    1,  117,    2, 0x06 /* Public */,
       5,    1,  120,    2, 0x06 /* Public */,
       6,    1,  123,    2, 0x06 /* Public */,
       7,    1,  126,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  129,    2, 0x0a /* Public */,
       9,    0,  130,    2, 0x0a /* Public */,
      10,    0,  131,    2, 0x0a /* Public */,
      11,    2,  132,    2, 0x0a /* Public */,
      14,    2,  137,    2, 0x0a /* Public */,
      15,    2,  142,    2, 0x0a /* Public */,
      16,    1,  147,    2, 0x0a /* Public */,
      17,    1,  150,    2, 0x0a /* Public */,
      18,    1,  153,    2, 0x0a /* Public */,
      19,    1,  156,    2, 0x0a /* Public */,
      20,    1,  159,    2, 0x0a /* Public */,
      22,    1,  162,    2, 0x09 /* Protected */,
      25,    0,  165,    2, 0x09 /* Protected */,
      26,    0,  166,    2, 0x09 /* Protected */,
      27,    0,  167,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      28, QMetaType::QString, 0x00495103,
      29, QMetaType::QString, 0x00495103,
      21, QMetaType::Bool, 0x00495103,
      30, QMetaType::Int, 0x00495103,
      31, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void GLItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLItem *_t = static_cast<GLItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->vertexShaderFilenameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->fragmentShaderFilenameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->movementActivatedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->viewportXChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->viewportYChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->paintBefore(); break;
        case 6: _t->paintAfter(); break;
        case 7: _t->toggleMove(); break;
        case 8: _t->mousePressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->mousePositionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->mouseReleased((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->setVertexShaderFilename((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->setFragmentShaderFilename((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->setViewportX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->setViewportY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->setMovementActivated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->handleWindowChanged((*reinterpret_cast< QQuickWindow*(*)>(_a[1]))); break;
        case 17: _t->onTimerTimeout(); break;
        case 18: _t->synchronizeThreads(); break;
        case 19: _t->deleteRenderer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GLItem::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLItem::vertexShaderFilenameChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GLItem::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLItem::fragmentShaderFilenameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GLItem::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLItem::movementActivatedChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GLItem::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLItem::viewportXChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (GLItem::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLItem::viewportYChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        GLItem *_t = static_cast<GLItem *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->vertexShaderFilename(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->fragmentShaderFilename(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->movementActivated(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->viewportX(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->viewportY(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        GLItem *_t = static_cast<GLItem *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVertexShaderFilename(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setFragmentShaderFilename(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setMovementActivated(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setViewportX(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setViewportY(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject GLItem::staticMetaObject = {
    { &QQuickItem::staticMetaObject, qt_meta_stringdata_GLItem.data,
      qt_meta_data_GLItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GLItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GLItem.stringdata0))
        return static_cast<void*>(const_cast< GLItem*>(this));
    return QQuickItem::qt_metacast(_clname);
}

int GLItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GLItem::vertexShaderFilenameChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLItem::fragmentShaderFilenameChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLItem::movementActivatedChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GLItem::viewportXChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GLItem::viewportYChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
