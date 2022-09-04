
DEFINES += QT_ASEMAN_EMBEDDED
contains(QT_ASEMAN_MODULES, core) {
    include ($$PWD/core/core.pri)
}
contains(QT_ASEMAN_MODULES, gui) {
    include ($$PWD/gui/gui.pri)
}
contains(QT_ASEMAN_MODULES, widgets) {
    include ($$PWD/widgets/widgets.pri)
}
contains(QT_ASEMAN_MODULES, network) {
    include ($$PWD/network/network.pri)
}
contains(QT_ASEMAN_MODULES, qml) {
    include ($$PWD/qml/qml.pri)
    include ($$PWD/asemanqml/asemanqml.pri)
}
contains(QT_ASEMAN_MODULES, sql) {
    include ($$PWD/sql/sql.pri)
}

lessThan(QT_MAJOR_VERSION, 6): { # Deprecated Modules
    contains(QT_ASEMAN_MODULES, multimedia) {
        include ($$PWD/multimedia/multimedia.pri)
    }
}
qtHaveModule(positioning): {
    contains(QT_ASEMAN_MODULES, geo) {
        include ($$PWD/geo/geo.pri)
    }
}
