load(qt_build_config)

TARGET = QAsemanWidgets
QT += asemancore asemangui

MODULE = asemanwidgets

load(qt_module)

DEFINES += LIBQTASEMAN_WIDGETS_LIBRARY

include (widgets.pri)
