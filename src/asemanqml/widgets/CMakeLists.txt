set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanwidgetsplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemwidgets.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanwidgetsplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemwidgets.cpp
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
