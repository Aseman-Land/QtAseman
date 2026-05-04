set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqmlplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitembase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandelegateswitch.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqmlplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitembase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandelegateswitch.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemanqml.qrc
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
