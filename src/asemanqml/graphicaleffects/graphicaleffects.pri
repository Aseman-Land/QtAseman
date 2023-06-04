INCLUDEPATH += $$PWD
QT += core gui quick

HEADERS += \
    $$PWD/asemangraphicaleffectsplugin.h \
    $$PWD/asemanqttoolsitemgraphicaleffects.h

SOURCES += \
    $$PWD/asemangraphicaleffectsplugin.cpp \
    $$PWD/asemanqttoolsitemgraphicaleffects.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

greaterThan(QT_MAJOR_VERSION, 5) {
    ASEMAN_QML_FILES = $$files($$PWD/GraphicalEffects/Qt6/*.*) $$PWD/GraphicalEffects/Qt6/qmldir
} else {
    ASEMAN_QML_FILES = $$files($$PWD/GraphicalEffects/Qt5/*.*) $$PWD/GraphicalEffects/Qt5/qmldir
}

INCLUDED_RESOURCE_FILES = \
    $$ASEMAN_QML_FILES

asemangraphicaleffects.files = $$INCLUDED_RESOURCE_FILES
asemangraphicaleffects.prefix = /AsemanQml/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemangraphicaleffects.qrc
} else {
    RESOURCES += asemangraphicaleffects
}
