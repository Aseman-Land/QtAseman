
android {
    QT += androidextras
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD

    OTHER_FILES += \
        $$PWD/AndroidManifest.xml \
        $$PWD/build.gradle \
        $$files($$PWD/*.png, true) \
        $$files($$PWD/*.xml, true)
}
