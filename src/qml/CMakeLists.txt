set(LOCAL_SOURCE
    ${LOCAL_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanapplicationitem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanbackhandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandragarea.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandragobject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanitemgrabber.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmouseeventlistener.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqmlengine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqmlimage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttools.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickobject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickview.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickviewwrapper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/qtsingleapplication/qtlocalpeer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/qtsingleapplication/qtlockedfile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantools_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandevicesitem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantoolsitem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanfileresourcemanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanproxycomponent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanapplicationsingleton.h

    ${CMAKE_CURRENT_SOURCE_DIR}/asemanapplicationitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanbackhandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandragarea.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandragobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanitemgrabber.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanmouseeventlistener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqmlengine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqmlimage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanqttools.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickview.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanquickviewwrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qtsingleapplication/qtlocalpeer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qtsingleapplication/qtlockedfile_unix.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/qtsingleapplication/qtlockedfile_win.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qtsingleapplication/qtlockedfile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemandevicesitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemantoolsitem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanfileresourcemanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanproxycomponent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asemanapplicationsingleton.cpp
    )

if (IOS)
else ()
    set(LOCAL_SOURCE
        ${LOCAL_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/asemanprocess.h
        ${CMAKE_CURRENT_SOURCE_DIR}/asemanprocess.cpp
        )
endif ()

set(SOURCE
    ${SOURCE}
    ${LOCAL_SOURCE}
    PARENT_SCOPE)

set(ASEMAN_INCLUDE_DIRS
    ${ASEMAN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
