CXX_MODULE = qml
TARGET = qtgraphicaleffectsplugin
TARGETPATH = QtGraphicalEffects
QT += quick qml
QT_PRIVATE += quick-private
IMPORT_VERSION = 1.$$QT_MINOR_VERSION
QML_FILES = \
    BrightnessContrast.qml \
    Colorize.qml \
    ColorOverlay.qml \
    ConicalGradient.qml \
    Desaturate.qml \
    Displace.qml \
    DropShadow.qml \
    FastBlur.qml \
    FastGlow.qml \
    GammaAdjust.qml \
    Glow.qml \
    HueSaturation.qml \
    LevelAdjust.qml \
    LinearGradient.qml \
    OpacityMask.qml \
    RadialGradient.qml \
    RectangularGlow.qml \
    ThresholdMask.qml

# !static: CONFIG += qmlcache

RESOURCES += \
    qtgraphicaleffectsshaders.qrc

SOURCES += qgfxsourceproxy.cpp plugin.cpp
HEADERS += qgfxsourceproxy_p.h
load(qml_plugin)
