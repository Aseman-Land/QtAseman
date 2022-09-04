QT += qml

HEADERS += \
    $$PWD/materialiconsplugin.h

SOURCES += \ 
    $$PWD/materialiconsplugin.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES = $$files($$PWD/MaterialIcons/*.*)

INCLUDED_RESOURCE_FILES = \
    $$ASEMAN_QML_FILES

asemanmaterialicons.files = $$INCLUDED_RESOURCE_FILES
asemanmaterialicons.prefix = /AsemanQml/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemanmaterialicons.qrc
} else {
    RESOURCES += asemanmaterialicons
}
