load(qt_build_config)

INCLUDEPATH += $$PWD $$PWD/../core $$PWD/../gui $$PWD/../network $$PWD/../widgets
DEPENDPATH += $$PWD

TARGET = QAsemanQml
QT = core gui asemancore asemangui asemannetwork network qml quick asemanwidgets
ios: QT += widgets

MODULE = asemanqml

load(qt_module)

DEFINES += LIBQTASEMAN_QML_LIBRARY

HEADERS += \
    $$PWD/asemanapplicationitem.h \
    $$PWD/asemanbackhandler.h \
    $$PWD/asemandragarea.h \
    $$PWD/asemandragobject.h \
    $$PWD/asemanitemgrabber.h \
    $$PWD/asemanmouseeventlistener.h \
    $$PWD/asemanqmlengine.h \
    $$PWD/asemanqmlimage.h \
    $$PWD/asemanqttools.h \
    $$PWD/asemanquickobject.h \
    $$PWD/asemanquickview.h \
    $$PWD/asemanquickviewwrapper.h \
    $$PWD/qtsingleapplication/qtlocalpeer.h \
    $$PWD/qtsingleapplication/qtlockedfile.h \
    $$PWD/asemantools_global.h \
    $$PWD/asemandevicesitem.h \
    $$PWD/asemantoolsitem.h \
    $$PWD/asemanfileresourcemanager.h \
    $$PWD/asemanproxycomponent.h 

SOURCES += \
    $$PWD/asemanapplicationitem.cpp \
    $$PWD/asemanbackhandler.cpp \
    $$PWD/asemandragarea.cpp \
    $$PWD/asemandragobject.cpp \
    $$PWD/asemanitemgrabber.cpp \
    $$PWD/asemanmouseeventlistener.cpp \
    $$PWD/asemanqmlengine.cpp \
    $$PWD/asemanqmlimage.cpp \
    $$PWD/asemanqttools.cpp \
    $$PWD/asemanquickobject.cpp \
    $$PWD/asemanquickview.cpp \
    $$PWD/asemanquickviewwrapper.cpp \
    $$PWD/qtsingleapplication/qtlocalpeer.cpp \
    $$PWD/qtsingleapplication/qtlockedfile_unix.cpp \
    $$PWD/qtsingleapplication/qtlockedfile_win.cpp \
    $$PWD/qtsingleapplication/qtlockedfile.cpp \
    $$PWD/asemandevicesitem.cpp \
    $$PWD/asemantoolsitem.cpp \
    $$PWD/asemanfileresourcemanager.cpp \
    $$PWD/asemanproxycomponent.cpp

android {
    QT += androidextras
}
win {
    QT += winextras
}
macx {
    !contains(QMAKE_HOST.arch, x86_64) {
        LIBS +=  -framework CoreFoundation -framework Carbon -lobjc
    }
    QT += macextras
}
ios {
    HEADERS += \
        $$PWD/private/osxviewcontroller.h
    SOURCES += \
        $$PWD/private/osxviewcontroller.mm
} else {
    HEADERS += \
        $$PWD/asemanprocess.h
    SOURCES += \
        $$PWD/asemanprocess.cpp
}

DISTFILES +=

