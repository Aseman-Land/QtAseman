
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemansql_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemansqlobject.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemansqlobject.cpp
    PARENT_SCOPE)
