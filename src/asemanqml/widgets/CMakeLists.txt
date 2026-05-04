
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanwidgetsplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemwidgets.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanwidgetsplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemwidgets.cpp
    PARENT_SCOPE)
