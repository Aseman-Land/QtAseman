TARGET  = asemanqmlmultimedia
TARGETPATH = AsemanQml/Multimedia
IMPORT_VERSION = 2.0

QT += asemanqml asemangui asemancore
lessThan(QT_MAJOR_VERSION, 6): QT += asemanmultimedia

include(multimedia.pri)

load(qml_plugin)

