set(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandownloader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanfiledownloaderqueue.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanfiledownloaderqueueitem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanhostchecker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkproxy.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetwork_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemansocketinterface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkrequestobject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkrequestmanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkquickobject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkrequestreply.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemandownloader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanfiledownloaderqueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanfiledownloaderqueueitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanhostchecker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkproxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemansocketinterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkrequestobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkrequestmanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkquickobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkrequestreply.cpp
    PARENT_SCOPE)

if (!WASM)
    set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkmanager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworksleepmanager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkmanageritem.h

        ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkmanager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworksleepmanager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asemannetworkmanageritem.cpp
        PARENT_SCOPE)
endif ()

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
