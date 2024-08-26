/****************************************************************************
** Meta object code from reading C++ file 'databasemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../databasemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'databasemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DatabaseManager_t {
    QByteArrayData data[25];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DatabaseManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DatabaseManager_t qt_meta_stringdata_DatabaseManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DatabaseManager"
QT_MOC_LITERAL(1, 16, 7), // "addList"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "name"
QT_MOC_LITERAL(4, 30, 11), // "description"
QT_MOC_LITERAL(5, 42, 7), // "addTask"
QT_MOC_LITERAL(6, 50, 6), // "listId"
QT_MOC_LITERAL(7, 57, 11), // "getAllLists"
QT_MOC_LITERAL(8, 69, 11), // "getAllTasks"
QT_MOC_LITERAL(9, 81, 8), // "editList"
QT_MOC_LITERAL(10, 90, 2), // "id"
QT_MOC_LITERAL(11, 93, 7), // "replace"
QT_MOC_LITERAL(12, 101, 6), // "listid"
QT_MOC_LITERAL(13, 108, 3), // "src"
QT_MOC_LITERAL(14, 112, 4), // "dest"
QT_MOC_LITERAL(15, 117, 9), // "checkTask"
QT_MOC_LITERAL(16, 127, 8), // "finished"
QT_MOC_LITERAL(17, 136, 7), // "getList"
QT_MOC_LITERAL(18, 144, 8), // "editTask"
QT_MOC_LITERAL(19, 153, 10), // "deleteTask"
QT_MOC_LITERAL(20, 164, 10), // "deleteList"
QT_MOC_LITERAL(21, 175, 12), // "getAllULists"
QT_MOC_LITERAL(22, 188, 12), // "getAllFLists"
QT_MOC_LITERAL(23, 201, 12), // "getAllUTasks"
QT_MOC_LITERAL(24, 214, 12) // "getAllFTasks"

    },
    "DatabaseManager\0addList\0\0name\0description\0"
    "addTask\0listId\0getAllLists\0getAllTasks\0"
    "editList\0id\0replace\0listid\0src\0dest\0"
    "checkTask\0finished\0getList\0editTask\0"
    "deleteTask\0deleteList\0getAllULists\0"
    "getAllFLists\0getAllUTasks\0getAllFTasks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DatabaseManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x02 /* Public */,
       5,    2,   94,    2, 0x02 /* Public */,
       7,    0,   99,    2, 0x02 /* Public */,
       8,    1,  100,    2, 0x02 /* Public */,
       9,    3,  103,    2, 0x02 /* Public */,
      11,    3,  110,    2, 0x02 /* Public */,
      15,    3,  117,    2, 0x02 /* Public */,
      17,    1,  124,    2, 0x02 /* Public */,
      18,    2,  127,    2, 0x02 /* Public */,
      19,    2,  132,    2, 0x02 /* Public */,
      20,    1,  137,    2, 0x02 /* Public */,
      21,    0,  140,    2, 0x02 /* Public */,
      22,    0,  141,    2, 0x02 /* Public */,
      23,    1,  142,    2, 0x02 /* Public */,
      24,    1,  145,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,    3,    6,
    QMetaType::QVariantList,
    QMetaType::QVariantList, QMetaType::Int,    6,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString, QMetaType::QString,   10,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   12,   13,   14,
    QMetaType::Bool, QMetaType::Int, QMetaType::Bool, QMetaType::Int,   10,   16,   12,
    QMetaType::QVariantMap, QMetaType::Int,   10,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   10,    3,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   10,   12,
    QMetaType::Bool, QMetaType::Int,   10,
    QMetaType::QVariantList,
    QMetaType::QVariantList,
    QMetaType::QVariantList, QMetaType::Int,    6,
    QMetaType::QVariantList, QMetaType::Int,    6,

       0        // eod
};

void DatabaseManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DatabaseManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->addList((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->addTask((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { QVariantList _r = _t->getAllLists();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariantList _r = _t->getAllTasks((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->editList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->replace((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: { bool _r = _t->checkTask((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariantMap _r = _t->getList((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->editTask((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->deleteTask((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->deleteList((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantList _r = _t->getAllULists();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 12: { QVariantList _r = _t->getAllFLists();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 13: { QVariantList _r = _t->getAllUTasks((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 14: { QVariantList _r = _t->getAllFTasks((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DatabaseManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DatabaseManager.data,
    qt_meta_data_DatabaseManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DatabaseManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DatabaseManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DatabaseManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DatabaseManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
