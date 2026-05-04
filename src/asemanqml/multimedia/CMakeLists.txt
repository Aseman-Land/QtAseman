set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmultimediaplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmultimedia.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmultimediaplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmultimedia.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemanmultimedia.qrc
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
