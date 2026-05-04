set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewportplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemviewport.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewport.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewportcontroller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewportcontrollerroute.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewportitem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanabstractviewporttype.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewportplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemviewport.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewport.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewportcontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewportcontrollerroute.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanviewportitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanabstractviewporttype.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemanviewport.qrc
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
