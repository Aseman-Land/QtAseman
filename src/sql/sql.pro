load(qt_build_config)

TARGET = QAsemanSql
QT += asemancore

MODULE = asemansql

load(qt_module)

DEFINES += LIBQTASEMAN_SQL_LIBRARY

include (sql.pri)
