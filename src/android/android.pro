TEMPLATE = subdirs
CONFIG   += ordered

lessThan(QT_MAJOR_VERSION, 6) {
    SUBDIRS  = java
} else {
    SUBDIRS  = java-qt6
}
