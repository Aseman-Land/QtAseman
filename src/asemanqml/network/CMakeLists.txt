
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemnetwork.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemnetwork.cpp
    PARENT_SCOPE)
