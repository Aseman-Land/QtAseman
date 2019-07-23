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
    id: sidemenu
    width: 100
    height: 62
    clip: true

    property Component delegate
    property variant item

    property real handleHeight: 20*Devices.density

    property alias menuHeight: item_frame.height
    property alias pressed: marea.pressed
    readonly property real percent: {
        var res = (menuHeight+item_frame.y)/menuHeight
        if(res < 0)
            res = 0
        else
        if(res > 1)
            res = 1
        return res
    }

    property int layoutDirection: 1
    readonly property bool showed: item_frame.y > -menuHeight

    onDelegateChanged: {
        if( item )
            item.destroy()
        if( !delegate )
            return

        item = delegate.createObject(item_parent)
    }

    Rectangle {
        anchors.fill: parent
        color: "#000000"
        opacity: Devices.isIOS? percent*0.7 : percent*0.5
    }

    Item {
        id: main_frame
        anchors.fill: parent
        transformOrigin: Item.Center
        rotation: layoutDirection? 180 : 0

        MouseArea {
            id: marea
            anchors.left: parent.left
            anchors.right: parent.right
            height: lastState? parent.height : handleHeight + menuHeight
            y: item_frame.y
            onMouseYChanged: {
                var newY = item_frame.y + mouseY-pinY
                if( newY > 0 )
                    newY = 0
                if( Math.abs(y-startY) > 5*Devices.density )
                    movedY = true

                item_frame.y = newY
            }
            onPressed: {
                pinY = mouseY
                item_frame.anim = false
                startY = y
                movedY = false
            }
            onReleased: {
                item_frame.anim = true

                var basePercent = lastState? 0.8 : 0.2

                if( !movedY ) {
                    return
                }

                if( sidemenu.percent > basePercent ) {
                    item_frame.y = 0
                    lastState = true
                } else {
                    item_frame.y = -menuHeight
                    lastState = false
                }
            }

            property real pinY: 0
            property bool lastState: false
            property real startY: 0
            property bool movedY: false

            onLastStateChanged: {
                if( lastState )
                    BackHandler.pushHandler(sidemenu,sidemenu.discard)
                else
                    BackHandler.removeHandler(sidemenu)
            }
        }

        Item {
            id: item_frame
            height: sidemenu.height
            width: parent.width
            y: -height

            onHeightChanged: {
                if(!marea.lastState)
                {
                    item_frame.anim = false
                    item_frame.y = -menuHeight
                }
            }

            property bool anim: false

            Behavior on y {
                NumberAnimation{ easing.type: Easing.OutCubic; duration: item_frame.anim? 400 : 0 }
            }

            Item {
                id: item_parent
                width: parent.width
                height: parent.height
                transformOrigin: Item.Center
                rotation: layoutDirection? 180 : 0
            }
        }

        Rectangle {
            id: shadow_rct
            anchors.top: item_frame.bottom
            height: 5*Devices.density
            width: parent.width
            opacity: Math.pow(percent, 0.1)
            visible: !Devices.isIOS
            gradient: Gradient {
                GradientStop { position: 1.0; color: "#00000000" }
                GradientStop { position: 0.0; color: "#33000000" }
            }
        }
    }

    function discard() {
        item_frame.anim = true
        item_frame.y = -menuHeight
        marea.lastState = false
    }

    function show() {
        item_frame.anim = true
        item_frame.y = 0
        marea.lastState = true
    }
}
