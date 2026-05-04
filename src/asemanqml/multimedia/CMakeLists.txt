
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmultimediaplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmultimedia.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmultimediaplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmultimedia.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemanmultimedia.qrc
    PARENT_SCOPE)
