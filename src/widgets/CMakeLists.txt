
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandesktoptools.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanfonthandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantaskbarbutton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanwidgets_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanabstracttaskbarbuttonengine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannotification.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemandesktoptools.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanfonthandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantaskbarbutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanabstracttaskbarbuttonengine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannotification.cpp
    PARENT_SCOPE)

if (ANDROID)
    add_compile_definitions(ANDROID_NATIVE_ASEMAN_NOTIFICATION)
    set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/asemanandroidnativenotification.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemanandroidnativenotification.cpp
        PARENT_SCOPE)
elseif (IOS)
else ()
    set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/asemansystemtray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemansystemtray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannativenotificationitem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannativenotificationitem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannativenotification.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannativenotification.cpp
        PARENT_SCOPE)
    if (LINUX)
        add_compile_definitions(LINUX_NATIVE_ASEMAN_NOTIFICATION)
        set(SOURCE
            ${SOURCE}
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanlinuxnativenotification.h
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanlinuxnativenotification.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanunitytaskbarbuttonengine.h
            ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanunitytaskbarbuttonengine.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/asemankdewallet.h
            ${CMAKE_CURRENT_SOURCE_DIR}/asemankdewallet.cpp
            PARENT_SCOPE)
    elseif (WIN32)
        set(SOURCE
            ${SOURCE}
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanwintaskbarbuttonengine.h
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanwintaskbarbuttonengine.cpp
            PARENT_SCOPE)
    elseif (MACOSX)
        add_compile_definitions(MAC_NATIVE_ASEMAN_NOTIFICATION)
        set(SOURCE
            ${SOURCE}
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanmacnativenotification.h
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanmacnativenotification.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanmactaskbarbuttonengine.h
            ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanmactaskbarbuttonengine.cpp
            PARENT_SCOPE)

    endif ()
endif ()
