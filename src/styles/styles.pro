TEMPLATE = subdirs
greaterThan(QT_MAJOR_VERSION, 5):greaterThan(QT_MINOR_VERSION, 13):qtHaveModule(quicktemplates2-private): SUBDIRS += iosstyle
