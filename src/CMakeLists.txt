
add_compile_definitions(QT_ASEMAN_EMBEDDED)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    SET(ASEMAN_COMPILE_DEFINITION ${ASEMAN_COMPILE_DEFINITION} ASEMAN_QT6)
endif ()

if (QT_ASEMAN_MODULES_CORE)
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/core)
endif ()
if (QT_ASEMAN_MODULES_GUI)
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/gui)
endif ()
if (QT_ASEMAN_MODULES_WIDGETS)
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/widgets)
endif ()
if (QT_ASEMAN_MODULES_NETWORK)
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/network)
endif ()
if (QT_ASEMAN_MODULES_QML)
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/qml)
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/asemanqml)
endif ()
if (QT_ASEMAN_MODULES_SQL)
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/sql)
endif ()

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6) # Deprecated Modules
else ()
    if (QT_ASEMAN_MODULES_MULTIMEDIA)
        add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/multimedia)
    endif ()
endif ()

if (Qt${QT_VERSION_MAJOR}::Positioning)
    if (QT_ASEMAN_MODULES_GEO)
        add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/geo)
    endif ()
endif ()

set(SOURCE
    ${SOURCE}
    PARENT_SCOPE)

set(ASEMAN_COMPILE_DEFINITION
    ${ASEMAN_COMPILE_DEFINITION}
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    PARENT_SCOPE)

set(ASEMAN_QML_IMPORT_PATH
    ${ASEMAN_QML_IMPORT_PATH}
    PARENT_SCOPE)
