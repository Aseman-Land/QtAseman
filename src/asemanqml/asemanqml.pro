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
    network \
    viewport \
    models \
    sql


greaterThan(QT_MAJOR_VERSION, 5) {
} else {
    SUBDIRS += multimedia
}
