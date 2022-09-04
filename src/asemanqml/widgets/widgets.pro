TARGET  = asemanqmlwidgets
TARGETPATH = AsemanQml/Widgets
IMPORT_VERSION = 2.0

QT += asemanqml asemangui asemancore asemanwidgets
include(widgets.pri)

load(qml_plugin)
