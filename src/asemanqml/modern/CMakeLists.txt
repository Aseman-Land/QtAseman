set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/modernplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmodern.h

    ${CMAKE_CURRENT_SOURCE_DIR}/modernplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmodern.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemanmodern.qrc
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
