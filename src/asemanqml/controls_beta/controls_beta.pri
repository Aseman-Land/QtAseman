INCLUDEPATH += $$PWD
QT += qml quick

HEADERS += \
    $$PWD/asemanquickabstractbutton.h \
    $$PWD/asemanquickabstractstyle.h \
    $$PWD/asemanquickboxsize.h \
    $$PWD/asemanquickcontrolitem.h \
    $$PWD/asemanquickmainpalette.h \
    $$PWD/asemanquickradiobuttoncontrol.h \
    $$PWD/asemanquickradiobuttongroup.h \
    $$PWD/asemanquicksceneitem.h \
    $$PWD/asemanquickscrollviewcore.h \
    $$PWD/asemanquickstyleattachedproperty.h \
    $$PWD/asemanquickstyleditem.h \
    $$PWD/asemanqttoolsitemcontrolsbeta.h \
    $$PWD/controlsbetaplugin.h


SOURCES += \
    $$PWD/asemanquickabstractbutton.cpp \
    $$PWD/asemanquickabstractstyle.cpp \
    $$PWD/asemanquickboxsize.cpp \
    $$PWD/asemanquickcontrolitem.cpp \
    $$PWD/asemanquickmainpalette.cpp \
    $$PWD/asemanquickradiobuttoncontrol.cpp \
    $$PWD/asemanquickradiobuttongroup.cpp \
    $$PWD/asemanquicksceneitem.cpp \
    $$PWD/asemanquickscrollviewcore.cpp \
    $$PWD/asemanquickstyleattachedproperty.cpp \
    $$PWD/asemanquickstyleditem.cpp \
    $$PWD/asemanqttoolsitemcontrolsbeta.cpp \
    $$PWD/controlsbetaplugin.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES = $$files($$PWD/Beta/*.*) $$PWD/Beta/qmldir
ASEMAN_QML_PRIVATES = $$files($$PWD/Beta/Private/*)
ASEMAN_QML_RESOURCES = $$files($$PWD/Beta/styles/simple/*)

INCLUDED_RESOURCE_FILES = \
    $$ASEMAN_QML_FILES \
    $$ASEMAN_QML_PRIVATES \
    $$ASEMAN_QML_RESOURCES

asemancontrols_beta.files = $$INCLUDED_RESOURCE_FILES
asemancontrols_beta.prefix = /AsemanQml/Controls/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemancontrols_beta.qrc
} else {
    RESOURCES += asemancontrols_beta
}

DISTFILES += \
    $$PWD/Beta/DialogScene.qml \
    $$PWD/Beta/ViewportContainer.qml \
    $$PWD/Beta/styles/simple/DialogSceneStyle.qml
