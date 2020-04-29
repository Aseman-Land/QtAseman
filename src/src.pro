TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
    core \
    gui \
    widgets \
    geo \
    multimedia \
    qml \
    network \
    asemanqml \
    styles

android: SUBDIRS += android

gui.depends += core
network.depends += core gui
widgets.depends += gui core
multimedia.depends += core gui
geo.depends += core gui
qml.depends += core gui widgets
asemanqml.depends += qml
