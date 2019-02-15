QT += quick network
android: QT += androidextras
CONFIG += c++11

SOURCES += main.cpp 
RESOURCES += qml.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
