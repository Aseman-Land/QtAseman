load(qt_build_config)

TARGET = QAsemanNetwork
QT = asemancore asemangui

MODULE = asemannetwork

load(qt_module)


DEFINES += LIBQTASEMAN_NETWORK_LIBRARY

include (network.pri)
