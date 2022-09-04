load(qt_build_config)

TARGET = QAsemanMultimedia
QT += asemancore

MODULE = asemanmultimedia

load(qt_module)

DEFINES += LIBQTASEMAN_MULTIMEDIA_LIBRARY

include (multimedia.pri)

