set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanapplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandevices.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanimagecoloranalizor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmimeapps.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmimedata.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantexttools.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantitlebarcolorgrabber.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantools.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantranslationmanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanwindowdetails.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemangui_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemankeyhandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanglobaltranslations.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanapplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandevices.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanimagecoloranalizor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmimeapps.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmimedata.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantexttools.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantitlebarcolorgrabber.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantools.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantranslationmanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanwindowdetails.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemankeyhandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanglobaltranslations.cpp
    PARENT_SCOPE)

if (ANDROID)
    set(SOURCE
        ${SOURCE}
        $$PWD/asemanjavalayer.cpp
        $$PWD/asemanjavalayer.h
        PARENT_SCOPE)
endif ()

if (IOS)
    set(SOURCE
        ${SOURCE}
        $$PWD/asemanobjectiveclayer.mm
        $$PWD/asemanobjectiveclayer.h
        PARENT_SCOPE)
    add_compile_definitions(DISABLE_IOS_CONTACTS_SUPPORT)
endif ()

if (MACOS)
    set(SOURCE
        ${SOURCE}
        $$PWD/asemanmacmanager.nn
        $$PWD/asemanmacmanager.h
        PARENT_SCOPE)
endif ()

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
