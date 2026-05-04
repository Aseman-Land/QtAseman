set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemnetwork.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemnetwork.cpp
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
