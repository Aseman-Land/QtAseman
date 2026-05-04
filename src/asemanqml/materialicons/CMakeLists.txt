
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/materialiconsplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/materialiconsplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemanmaterialicons.qrc
    PARENT_SCOPE)
