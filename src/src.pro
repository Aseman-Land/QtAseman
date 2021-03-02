TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
    core \
    gui \
    widgets \
    multimedia \
    qml \
    network \
    sql

qtHaveModule(geo): SUBDIRS += geo

SUBDIRS += \
    asemanqml \
    styles 

android: SUBDIRS += android
linux: !android: SUBDIRS += wizards

gui.depends += core
network.depends += core gui
widgets.depends += gui core
multimedia.depends += core gui
geo.depends += core gui
qml.depends += core gui widgets
asemanqml.depends += qml
