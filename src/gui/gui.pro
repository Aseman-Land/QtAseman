CONFIG += no_app_extension_api_only
load(qt_build_config)

TARGET = QAsemanGui
QT += asemancore

MODULE = asemangui

load(qt_module)

static: DEFINES += ASEMAN_STATIC_BUILD

DEFINES += LIBQTASEMAN_GUI_LIBRARY

include (gui.pri)
