@if "%{UseVirtualKeyboard}" == "true"
QT += quick virtualkeyboard
@else
QT += quick
@endif

CONFIG += c++11

QML_IMPORT_PATH += \\
    $$PWD/qml/imports

SOURCES += \\
        %{MainCppFileName}

RESOURCES += qml/qml.qrc
@if %{HasTranslation}

TRANSLATIONS += \\
    %{TsFileName}
@endif

QML_IMPORT_PATH =
