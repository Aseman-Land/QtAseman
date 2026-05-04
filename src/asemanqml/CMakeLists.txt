
add_subdirectory(base)
add_subdirectory(graphicaleffects)

if (ASEMAN_QML_MODULES_AWESOME)
    add_subdirectory(awesome)
endif ()

if (ASEMAN_QML_MODULES_MATERIALICONS)
    add_subdirectory(materialicons)
endif ()

if (ASEMAN_QML_MODULES_MULTIMEDIA)
    add_subdirectory(multimedia)
endif ()

if (ASEMAN_QML_MODULES_WIDGETS)
    add_subdirectory(widgets)
endif ()

if (ASEMAN_QML_MODULES_MODERN)
    add_subdirectory(modern)
endif ()

if (ASEMAN_QML_MODULES_CONTROLS)
    add_subdirectory(controls)
endif ()

if (ASEMAN_QML_MODULES_CONTROLS_BETA)
    add_subdirectory(controls_beta)
endif ()

if (ASEMAN_QML_MODULES_NETWORK)
    add_subdirectory(network)
endif ()

if (ASEMAN_QML_MODULES_VIEWPORT)
    add_subdirectory(viewport)
endif ()

if (ASEMAN_QML_MODULES_MODELS)
    add_subdirectory(models)
endif ()

if (ASEMAN_QML_MODULES_SQL)
    add_subdirectory(sql)
endif ()

# if (ASEMAN_QML_MODULES_GRAPHICAL_EFFECTS)
#     add_subdirectory(graphicaleffects)
# endif ()

set(SOURCE
    ${SOURCE}
    PARENT_SCOPE)

set(ASEMAN_COMPILE_DEFINITION
    ${ASEMAN_COMPILE_DEFINITION}
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)

set(ASEMAN_QML_IMPORT_PATH
    ${ASEMAN_QML_IMPORT_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/import
    PARENT_SCOPE)
