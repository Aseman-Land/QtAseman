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
    $$PWD/asemanquickstyleditem.h

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
    $$PWD/asemanquickstyleditem.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_BETA_FILES = $$files($$PWD/*.qml) $$PWD/qmldir
ASEMAN_QML_BETA_PRIVATES = $$files($$PWD/private/*)
ASEMAN_QML_BETA_RESOURCES = $$files($$PWD/styles/simple/*)

INCLUDED_BETA_RESOURCE_FILES = \
    $$ASEMAN_QML_BETA_FILES \
    $$ASEMAN_QML_BETA_PRIVATES \
    $$ASEMAN_QML_BETA_RESOURCES

asemancontrolsbeta.files = $$INCLUDED_BETA_RESOURCE_FILES
asemancontrolsbeta.prefix = /AsemanQml/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemancontrolsbeta.qrc
} else {
    RESOURCES += asemancontrolsbeta
}
