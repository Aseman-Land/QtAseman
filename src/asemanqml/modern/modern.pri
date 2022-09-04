INCLUDEPATH += $$PWD
QT += qml core gui

HEADERS += \
    $$PWD/modernplugin.h \
    $$PWD/asemanqttoolsitemmodern.h

SOURCES += \
    $$PWD/modernplugin.cpp \
    $$PWD/asemanqttoolsitemmodern.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES = $$files($$PWD/Modern/*.*) $$PWD/Modern/qmldir

INCLUDED_RESOURCE_FILES = \
    $$ASEMAN_QML_FILES

asemanmodern.files = $$INCLUDED_RESOURCE_FILES
asemanmodern.prefix = /AsemanQml/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemanmodern.qrc
} else {
    RESOURCES += asemanmodern
}
