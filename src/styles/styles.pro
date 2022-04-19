TEMPLATE = subdirs

#lessThan(QT_MAJOR_VERSION, 6): {
    qtHaveModule(quicktemplates2-private): SUBDIRS += iosstyle
#}
