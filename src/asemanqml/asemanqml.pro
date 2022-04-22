TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    base \
    awesome \
    materialicons \
    multimedia \
    widgets \
    modern \
    controls \
    network \
    viewport \
    models \
    sql \

greaterThan(QT_MAJOR_VERSION, 5): SUBDIRS += graphicaleffects
