
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemansqlplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemsql.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicksqlobject.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemansqlplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemsql.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicksqlobject.cpp
    PARENT_SCOPE)
