set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanlocationlistener.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemangeo_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanabstractlocationlistenercore.h
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanqtlocationlistenercore.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanlocationlistener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanabstractlocationlistenercore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanqtlocationlistenercore.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/asemancoreresource_lib.qrc
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
