
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/modernplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmodern.h

    ${CMAKE_CURRENT_SOURCE_DIR}/modernplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmodern.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemanmodern.qrc
    PARENT_SCOPE)
