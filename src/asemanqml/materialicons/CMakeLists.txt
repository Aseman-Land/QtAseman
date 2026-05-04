set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/materialiconsplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/materialiconsplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemanmaterialicons.qrc
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)

