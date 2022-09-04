QT += qml

HEADERS += \
    $$PWD/awesomeplugin.h

SOURCES += \
    $$PWD/awesomeplugin.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES = $$files($$PWD/Awesome/*.*)

INCLUDED_RESOURCE_FILES = \
    $$ASEMAN_QML_FILES

asemanawesome.files = $$INCLUDED_RESOURCE_FILES
asemanawesome.prefix = /AsemanQml/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemanawesome.qrc
} else {
    RESOURCES += asemanawesome
}

