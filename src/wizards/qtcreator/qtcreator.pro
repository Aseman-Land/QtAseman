TEMPLATE = aux
CONFIG -= qt android_install

wizardresources.files = \
    $$PWD/qtasemanapplication

wizardresources.path = $$[QT_INSTALL_PREFIX]/share/qtcreator/templates/wizards/projects/

INSTALLS += wizardresources

!prefix_build:!equals(OUT_PWD, $$PWD) {
    RETURN = $$escape_expand(\\n\\t)
    equals(QMAKE_HOST.os, Windows) {
        RETURN = $$escape_expand(\\r\\n\\t)
    }
    OUT_PATH = $$shell_path($$OUT_PWD)

    QMAKE_POST_LINK += \
        $${QMAKE_COPY_DIR} $$shell_path($$PWD/qtasemanapplication) $$OUT_PATH
}
