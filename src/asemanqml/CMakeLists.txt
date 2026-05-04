
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

if (QT_ASEMAN_MODULES_SQL)
    add_subdirectory(sql)
endif ()

if (QT_ASEMAN_MODULES_GRAPHICAL_EFFECTS)
    add_subdirectory(graphicaleffects)
endif ()
