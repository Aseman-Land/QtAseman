set(LOCAL_SOURCE
    ${LOCAL_SOURCE}
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
    )

if (ANDROID)
    SET(ASEMAN_COMPILE_DEFINITION ${ASEMAN_COMPILE_DEFINITION} ANDROID_NATIVE_ASEMAN_NOTIFICATION)
    set(LOCAL_SOURCE
        ${LOCAL_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/asemanandroidnativenotification.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemanandroidnativenotification.cpp
        )
elseif (IOS)
else ()
    set(LOCAL_SOURCE
        ${LOCAL_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/asemansystemtray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemansystemtray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannativenotificationitem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannativenotificationitem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannativenotification.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannativenotification.cpp
        )

    if (LINUX)
        SET(ASEMAN_COMPILE_DEFINITION ${ASEMAN_COMPILE_DEFINITION} LINUX_NATIVE_ASEMAN_NOTIFICATION)
        set(LOCAL_SOURCE
            ${LOCAL_SOURCE}
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanlinuxnativenotification.h
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanlinuxnativenotification.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanunitytaskbarbuttonengine.h
            ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanunitytaskbarbuttonengine.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/asemankdewallet.h
            ${CMAKE_CURRENT_SOURCE_DIR}/asemankdewallet.cpp
            )
    elseif (WIN32)
        set(LOCAL_SOURCE
            ${LOCAL_SOURCE}
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanwintaskbarbuttonengine.h
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanwintaskbarbuttonengine.cpp
            )
    elseif (MACOSX)
        SET(ASEMAN_COMPILE_DEFINITION ${ASEMAN_COMPILE_DEFINITION} MAC_NATIVE_ASEMAN_NOTIFICATION)
        set(LOCAL_SOURCE
            ${LOCAL_SOURCE}
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanmacnativenotification.h
            ${CMAKE_CURRENT_SOURCE_DIR}/asemanmacnativenotification.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanmactaskbarbuttonengine.h
            ${CMAKE_CURRENT_SOURCE_DIR}/private/asemanmactaskbarbuttonengine.cpp
            )

    endif ()
endif ()

set(SOURCE
    ${SOURCE}
    ${LOCAL_SOURCE}
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)

set(ASEMAN_COMPILE_DEFINITION
    ${ASEMAN_COMPILE_DEFINITION}
    PARENT_SCOPE)
