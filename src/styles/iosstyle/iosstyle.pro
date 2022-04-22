TARGET = qtquickcontrols2iosstylestyleplugin
IMPORT_VERSION = 2.5

greaterThan(QT_MAJOR_VERSION, 5) {
    TARGETPATH = QtQuick/Controls/IOSStyle
} else {
    TARGETPATH = QtQuick/Controls.2/IOSStyle
}

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private quicktemplates2-private quickcontrols2-private

greaterThan(QT_MAJOR_VERSION, 5): QT_PRIVATE += quickcontrols2impl-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

include(iosstyle.pri)

OTHER_FILES += \
    qmldir \
    $$QML_FILES

SOURCES += \
    $$PWD/qtquickcontrols2iosstylestyleplugin.cpp

RESOURCES += \
    $$PWD/qtquickcontrols2iosstylestyleplugin.qrc

CONFIG += no_cxx_module install_qml_files builtin_resources qtquickcompiler
load(qml_plugin)

#requires(qtConfig(quickcontrols2-iosstyle))
