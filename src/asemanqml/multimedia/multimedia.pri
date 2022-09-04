INCLUDEPATH += $$PWD
QT += core gui network multimedia qml

HEADERS += \
    $$PWD/asemanmultimediaplugin.h \
    $$PWD/asemanqttoolsitemmultimedia.h

SOURCES += \
    $$PWD/asemanmultimediaplugin.cpp \
    $$PWD/asemanqttoolsitemmultimedia.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES = $$files($$PWD/Multimedia/*.*) $$PWD/Multimedia/qmldir

INCLUDED_RESOURCE_FILES = \
    $$ASEMAN_QML_FILES

asemanmultimedia.files = $$INCLUDED_RESOURCE_FILES
asemanmultimedia.prefix = /AsemanQml/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemanmultimedia.qrc
} else {
    RESOURCES += asemanmultimedia
}

