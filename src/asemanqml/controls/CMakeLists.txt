set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/controlsplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemcontrols.h

    ${CMAKE_CURRENT_SOURCE_DIR}/controlsplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemcontrols.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemancontrols.qrc
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
