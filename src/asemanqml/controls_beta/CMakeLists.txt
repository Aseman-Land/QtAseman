
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickabstractbutton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickabstractstyle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickboxsize.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickcolumnlayout.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickcontrolitem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklayout.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickmainpalette.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickradiobuttoncontrol.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickradiobuttongroup.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickrowlayout.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicksceneitem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickscrollviewcore.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickstyleattachedproperty.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickstyleditem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemcontrolsbeta.h
    ${CMAKE_CURRENT_SOURCE_DIR}/controlsbetaplugin.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickabstractbutton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickabstractstyle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickboxsize.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickcolumnlayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickcontrolitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicklayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickmainpalette.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickradiobuttoncontrol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickradiobuttongroup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickrowlayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquicksceneitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickscrollviewcore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickstyleattachedproperty.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickstyleditem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttoolsitemcontrolsbeta.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/controlsbetaplugin.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/qmake_asemancontrols_beta.qrc
    PARENT_SCOPE)
