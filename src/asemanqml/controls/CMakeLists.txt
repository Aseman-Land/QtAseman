
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/controlsplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemcontrols.h

    ${CMAKE_CURRENT_SOURCE_DIR}/controlsplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemcontrols.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemancontrols.qrc
    PARENT_SCOPE)
