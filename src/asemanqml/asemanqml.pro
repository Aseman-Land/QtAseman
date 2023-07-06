TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    base \
    awesome \
    materialicons \
    graphicaleffects \
    widgets \
    modern \
    controls \
    controls_beta \
    network \
    viewport \
    models \
    sql


greaterThan(QT_MAJOR_VERSION, 5) {
} else {
    SUBDIRS += multimedia
}
