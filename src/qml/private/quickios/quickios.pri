# https://github.com/benlau/quickios/

QT += gui-private
CONFIG += no_app_extension_api_only

HEADERS += \
    $$PWD/quickios.h \
    $$PWD/qiviewdelegate.h \
    $$PWD/qidevice.h \
    $$PWD/qiimagepicker.h \
    $$PWD/qisystemdispatcher.h

SOURCES += \
    $$PWD/quickios.cpp \
    $$PWD/qidevice.cpp \
    $$PWD/qiimagepicker.cpp \
    $$PWD/qisystemdispatcher.cpp


QMAKE_CXXFLAGS += -fobjc-arc

OBJECTIVE_SOURCES += \
    $$PWD/qisystemutils.mm \
    $$PWD/qiviewdelegate.mm \
    $$PWD/qidevice.mm

