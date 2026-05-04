set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemangraphicaleffectsplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemgraphicaleffects.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemangraphicaleffectsplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemgraphicaleffects.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemangraphicaleffects.qrc
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)

