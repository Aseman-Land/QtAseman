
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemangraphicaleffectsplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemgraphicaleffects.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemangraphicaleffectsplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemgraphicaleffects.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemangraphicaleffects.qrc
    PARENT_SCOPE)
