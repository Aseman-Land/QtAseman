INCLUDEPATH += $$PWD
QT += core gui network quick

HEADERS += \
    $$PWD/asemanviewportplugin.h \
    $$PWD/asemanqttoolsitemviewport.h \
    $$PWD/asemanviewport.h \
    $$PWD/asemanviewportcontroller.h \
    $$PWD/asemanviewportcontrollerroute.h \
    $$PWD/asemanviewportitem.h \
    $$PWD/asemanabstractviewporttype.h

SOURCES += \
    $$PWD/asemanviewportplugin.cpp \
    $$PWD/asemanqttoolsitemviewport.cpp \
    $$PWD/asemanviewport.cpp \
    $$PWD/asemanviewportcontroller.cpp \
    $$PWD/asemanviewportcontrollerroute.cpp \
    $$PWD/asemanviewportitem.cpp \
    $$PWD/asemanabstractviewporttype.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES = $$files($$PWD/Viewport/*.*) $$PWD/Viewport/qmldir

INCLUDED_RESOURCE_FILES = \
    $$ASEMAN_QML_FILES

asemanviewport.files = $$INCLUDED_RESOURCE_FILES
asemanviewport.prefix = /AsemanQml/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemanviewport.qrc
} else {
    RESOURCES += asemanviewport
}

DISTFILES += \
    Viewport/ViewportController.qml

