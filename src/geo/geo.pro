load(qt_build_config)

TARGET = QAsemanGeo
QT = asemancore

MODULE = asemangeo

load(qt_module)

DEFINES += LIBQTASEMAN_GEO_LIBRARY

include(geo.pri)
