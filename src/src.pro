TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
    core \
    gui \
    network \
    widgets \
    multimedia \
    qml \
    asemanqml \
    styles

android: SUBDIRS += android

gui.depends += core
network.depends += core gui
widgets.depends += gui core
multimedia.depends += core gui
qml.depends += core gui widgets
asemanqml.depends += qml
