ios {
    CONFIG += no_app_extension_api_only
}

load(qt_build_config)

TARGET = QAsemanQml
QT += asemancore asemangui asemanwidgets asemannetwork

MODULE = asemanqml

load(qt_module)

DEFINES += LIBQTASEMAN_QML_LIBRARY

include (qml.pri)
