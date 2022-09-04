TARGET  = asemanqmlbase
TARGETPATH = AsemanQml/Base
IMPORT_VERSION = 2.0
VERSION_REVISION = 2

QT += asemanqml asemangui asemancore asemannetwork asemanwidgets
include(base.pri)

load(qml_plugin)
