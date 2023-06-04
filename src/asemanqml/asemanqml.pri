
include(base/base.pri)
include(graphicaleffects/graphicaleffects.pri)

contains(ASEMAN_QML_MODULES, awesome) {
    include(awesome/awesome.pri)
}

contains(ASEMAN_QML_MODULES, materialicons) {
    include(materialicons/materialicons.pri)
}

contains(ASEMAN_QML_MODULES, multimedia) {
    include(multimedia/multimedia.pri)
}

contains(ASEMAN_QML_MODULES, widgets) {
    include(widgets/widgets.pri)
}

contains(ASEMAN_QML_MODULES, modern) {
    include(modern/modern.pri)
}

contains(ASEMAN_QML_MODULES, controls) {
    include(controls/controls.pri)
}

contains(ASEMAN_QML_MODULES, network) {
    include(network/network.pri)
}

contains(ASEMAN_QML_MODULES, viewport) {
    include(viewport/viewport.pri)
}

contains(ASEMAN_QML_MODULES, models) {
    include(models/models.pri)
}

contains(QT_ASEMAN_MODULES, sql) {
    include(sql/sql.pri)
}

contains(QT_ASEMAN_MODULES, graphicaleffects) {
    greaterThan(QT_MAJOR_VERSION, 5): include(graphicaleffects/graphicaleffects.pri)
}
