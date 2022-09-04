
include(base/base.pri)
include(awesome/awesome.pri)
include(materialicons/materialicons.pri)
include(multimedia/multimedia.pri)
include(widgets/widgets.pri)
include(modern/modern.pri)
include(controls/controls.pri)
include(network/network.pri)
include(viewport/viewport.pri)
include(models/models.pri)

contains(QT_ASEMAN_MODULES, sql) {
    include(sql/sql.pri)
}

greaterThan(QT_MAJOR_VERSION, 5): include(graphicaleffects/graphicaleffects.pri)
