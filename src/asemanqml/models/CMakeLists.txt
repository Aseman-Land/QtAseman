
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmodelsplugin.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmodels.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodelsource.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanabstractquicklistmodelhint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodelcamelcasehint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodelcopyhint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodeldeletehint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodelformathint.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmodelsplugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemmodels.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodelsource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanabstractquicklistmodelhint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodelcamelcasehint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodelcopyhint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodeldeletehint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklistmodelformathint.cpp
    PARENT_SCOPE)
