INCLUDEPATH += $$PWD
QT += core gui network widgets qml

HEADERS += \
    $$PWD/asemanwidgetsplugin.h \
    $$PWD/asemanqttoolsitemwidgets.h

SOURCES += \
    $$PWD/asemanwidgetsplugin.cpp \
    $$PWD/asemanqttoolsitemwidgets.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD
