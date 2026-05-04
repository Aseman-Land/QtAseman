
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

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
