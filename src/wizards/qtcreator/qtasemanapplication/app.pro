@if "%{UseVirtualKeyboard}" == "true"
QT += quick virtualkeyboard
@else
QT += quick
@endif

CONFIG += c++11

include(ios/ios.pri)
include(android/android.pri)

exists ($$PWD/qml/imports): QML_IMPORT_PATH += $$PWD/qml/imports

SOURCES += \\
        %{MainCppFileName}

RESOURCES += qml/qml.qrc
@if %{HasTranslation}

TRANSLATIONS += \\
    %{TsFileName}
@endif
