TARGET = qtquickcontrols2iosstylestyleplugin
TARGETPATH = QtQuick/Controls.2/IOSStyle
IMPORT_VERSION = 2.5

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private quicktemplates2-private quickcontrols2-private

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
