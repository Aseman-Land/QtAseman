set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemansqlplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemsql.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicksqlobject.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemansqlplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemsql.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicksqlobject.cpp
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
