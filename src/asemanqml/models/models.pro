TARGET  = asemanqmlmodels
TARGETPATH = AsemanQml/Models
IMPORT_VERSION = 2.0

QT += asemanqml asemangui asemancore
include(models.pri)

load(qml_plugin)
