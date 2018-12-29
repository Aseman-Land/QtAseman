TEMPLATE = subdirs
SUBDIRS = \
    core \
    gui \
    network \
    widgets \
    geo \
    multimedia \
    qml \
    asemanqml

android: SUBDIRS += android

gui.depends += core
network.depends += core gui
widgets.depends += gui core
geo.depends += core gui
multimedia.depends += core gui
qml.depends += core gui widgets
asemanqml.depends += qml
