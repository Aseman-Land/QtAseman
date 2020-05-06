@if "%{UseVirtualKeyboard}" == "true"
QT += quick virtualkeyboard
@else
QT += quick
@endif

CONFIG += c++11

android {
    QT += androidextras
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}
ios {
    include(ios/ios.pri)
}

exists ($$PWD/qml/imports): QML_IMPORT_PATH += $$PWD/qml/imports

SOURCES += \\
        %{MainCppFileName}

RESOURCES += qml/qml.qrc
@if %{HasTranslation}

TRANSLATIONS += \\
    %{TsFileName}
@endif
