import qbs

CppApplication {
@if "%{UseVirtualKeyboard}" == "true"
    Depends { name: "Qt"; submodules: ["quick", "virtualkeyboard"] }
@else
    Depends { name: "Qt.quick" }
@endif

    // Additional import path used to resolve QML modules in Qt Creator's code model
    property pathList qmlImportPaths: []

    cpp.cxxLanguageVersion: "c++14"

    cpp.defines: [
        // The following define makes your compiler emit warnings if you use
        // any Qt feature that has been marked deprecated (the exact warnings
        // depend on your compiler). Please consult the documentation of the
        // deprecated API in order to know how to port your code away from it.
        "QT_DEPRECATED_WARNINGS",

        // You can also make your code fail to compile if it uses deprecated APIs.
        // In order to do so, uncomment the following line.
        // You can also select to disable deprecated APIs only up to a certain version of Qt.
        //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
    ]

    files: [
        "%{MainCppFileName}",
        "main.qml",
        "qml.qrc",
@if %{HasTranslation}
        "%{TsFileName}",
@endif
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
