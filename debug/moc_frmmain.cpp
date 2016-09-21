/****************************************************************************
** Meta object code from reading C++ file 'frmmain.h'
**
** Created: Mon Aug 15 10:54:39 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Video/frmmain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_frmMain[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,    9,    8,    8, 0x0a,
      42,   36,    8,    8, 0x0a,
      63,    8,    8,    8, 0x08,
      80,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_frmMain[] = {
    "frmMain\0\0enable\0slotSaveVideo(bool)\0"
    "image\0slotSetImage(QImage)\0slotVideoStart()\0"
    "slotCheckVideoFile()\0"
};

void frmMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        frmMain *_t = static_cast<frmMain *>(_o);
        switch (_id) {
        case 0: _t->slotSaveVideo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slotSetImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 2: _t->slotVideoStart(); break;
        case 3: _t->slotCheckVideoFile(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData frmMain::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject frmMain::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_frmMain,
      qt_meta_data_frmMain, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &frmMain::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *frmMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *frmMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_frmMain))
        return static_cast<void*>(const_cast< frmMain*>(this));
    return QWidget::qt_metacast(_clname);
}

int frmMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
