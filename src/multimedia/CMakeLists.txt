
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanaudioencodersettings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanaudiorecorder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemancameracapture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmultimedia_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanabstractcameracapturecore.h
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemannullcameracapturecore.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmultimediadatabase.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanaudioencodersettings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanaudiorecorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemancameracapture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanabstractcameracapturecore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemannullcameracapturecore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmultimediadatabase.cpp
    PARENT_SCOPE)

if (ANDROID)
    set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanandroidcameracapturecore.h
        ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanandroidcameracapturecore.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanandroidmultimedia.h
        ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanandroidmultimedia.cpp
        PARENT_SCOPE)
endif ()
