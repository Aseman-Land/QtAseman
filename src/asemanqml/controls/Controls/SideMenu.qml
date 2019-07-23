/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.9
import AsemanQml.Base 2.0

Item {
    id: sideMenu
    clip: true

    /*! Enums !*/
    readonly property int menuTypeModern: 0
    readonly property int menuTypeMaterial: 1

    property int menuType: Devices.isIOS? menuTypeModern : menuTypeMaterial

    onMenuTypeChanged: prv.refresh()

    property Component delegate
    property Item source
    readonly property Item menuItem: {
        if(prv.drawerItem)
            return prv.drawerItem
        if(prv.menuControllerItem)
            return prv.menuControllerItem
        return null
    }

    property real handleWidth: 20*Devices.density
    property real menuWidth: {
        if(prv.drawerItem)
            return prv.drawerItem.menuWidth
        if(prv.menuControllerItem)
            return prv.menuControllerItem.menuWidth
        return width*0.8
    }

    readonly property bool showed: {
        if(prv.drawerItem)
            return prv.drawerItem.showed
        if(prv.menuControllerItem)
            return prv.menuControllerItem.isVisible
        return false
    }
    readonly property bool pressed: {
        if(prv.drawerItem)
            return prv.drawerItem.pressed
        if(prv.menuControllerItem)
            return prv.menuControllerItem.pressed
        return false
    }
    readonly property real percent: {
        if(prv.drawerItem)
            return prv.drawerItem.percent
        if(prv.menuControllerItem)
            return prv.menuControllerItem.ratio
        return 0
    }

    property int layoutDirection: View.layoutDirection
    QtObject {
        id: prv
        property Drawer drawerItem
        property MenuController menuControllerItem

        function refresh() {
            switch(menuType) {
            case menuTypeMaterial:
                if(drawerItem)
                    return

                drawerItem = drawer_component.createObject(sideMenu)
                if(menuControllerItem)
                    menuControllerItem.destroy()
                break;

            case menuTypeModern:
                if(menuControllerItem)
                    return

                menuControllerItem = menuController_component.createObject(sideMenu)
                if(drawerItem)
                    drawerItem.destroy()
                break;
            }
        }
    }

    function discard() {
        if(prv.drawerItem)
            return prv.drawerItem.discard()
        if(prv.menuControllerItem)
            return prv.menuControllerItem.close()
    }

    function show() {
        if(prv.drawerItem)
            return prv.drawerItem.show()
        if(prv.menuControllerItem)
            return prv.menuControllerItem.show()
    }

    Component {
        id: drawer_component
        Drawer {
            anchors.fill: parent
            delegate: sideMenu.delegate
            layoutDirection: sideMenu.layoutDirection
            handleWidth: sideMenu.handleWidth
        }
    }

    Component {
        id: menuController_component
        MenuController {
            anchors.fill: parent
            source: sideMenu.source
            component: sideMenu.delegate
            layoutDirection: sideMenu.layoutDirection
            handleWidth: sideMenu.handleWidth
        }
    }

    Component.onCompleted: prv.refresh()
}
