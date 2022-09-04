TARGET  = asemanqmlsql
TARGETPATH = AsemanQml/Sql
IMPORT_VERSION = 2.0

QT += asemanqml asemangui asemancore asemansql

include(sql.pri)

load(qml_plugin)

