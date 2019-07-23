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
    id: p_dialog
    anchors.fill: parent
    visible: back.opacity != 0

    property variant item
    property real margin: 10
    property bool hoverToClose: false
    property alias containsMouse: back_marea.containsMouse

    property real extraX: 0
    property real extraY: 7*Devices.density

    property real pointerLeftMargin: pointer.width

    onVisibleChanged: {
        if( visible )
            BackHandler.pushHandler(p_dialog,p_dialog.hide)
        else
            BackHandler.removeHandler(p_dialog)
    }

    MouseArea {
        id: marea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: p_dialog.hide()
        onWheel: wheel.accepted = true
        onPositionChanged: {
            if(!containsMouse || !hoverToClose || hover_disabler_timer.running) {
                hover_close_timer.stop()
                return
            }

            hover_close_timer.restart()
        }
    }

    Timer {
        id: hover_disabler_timer
        interval: 400
    }

    Timer {
        id: hover_close_timer
        interval: 200
        onTriggered: if(marea.containsMouse) p_dialog.hide()
    }

    QtObject {
        id: privates
        property variant lastItem
    }

    AnimationItem {
        id: back
        scale: 1 - 1/40 + opacity/40
        opacity: 0
        transformOrigin: mirror? Item.Bottom : Item.Top

        property bool mirror: false

        onWidthChanged: refresh()
        onHeightChanged: refresh()

        BorderImage {
            id: border
            source: "files/pointer-dialog.png"
            anchors.fill: parent
            border.left: 14
            border.top: 14
            border.right: 14
            border.bottom: 14
        }

        Image {
            id: pointer
            source: back.mirror? "files/pointer-down.png" : "files/pointer.png"
            width: 42*Devices.density
            height: 20*Devices.density
            smooth: true
            anchors.bottom: back.mirror? border.bottom : border.top
            anchors.bottomMargin: back.mirror? 10 - 20*Devices.density : -11
            anchors.left: parent.left
            anchors.leftMargin: pointerLeftMargin
        }

        MouseArea {
            id: back_marea
            hoverEnabled: true
            anchors.fill: parent
            anchors.margins: -20*Devices.density
            z: 10
            onPressed: mouse.accepted = false
            onWheel: wheel.accepted = false
        }

        Behavior on y {
            NumberAnimation { easing.type: back.easing.type; duration: back.anim? back.anim_time : 0 }
        }
        Behavior on opacity {
            NumberAnimation { easing.type: back.easing.type; duration: back.anim? back.anim_time : 0 }
        }
    }

    onItemChanged: {
        if( !item )
            return
        if( privates.lastItem )
            privates.lastItem.destroy()

        item.parent = back
        privates.lastItem = item
        refresh()
    }

    function refresh(){
        if( !item )
            return

        item.x = margin
        item.y = margin
        item.width = back.width - 2*margin
        item.height = back.height - 2*margin
    }

    function pointingTo( x, y, width, height ){
        if( x < 0 )
            x = 0
        if( y < 0 )
            y = 0
        if( x + width > p_dialog.width )
            width = p_dialog.width - x
        if( y > p_dialog.height )
            height = p_dialog.height

        if( y > p_dialog.height/2 ) {
            back.mirror = true
            y = y - height
        } else {
            back.mirror = false
        }

        hover_disabler_timer.restart()

        back.x = x - extraX
        back.y = back.mirror? y + extraY : y - extraY
        back.width = width
        back.height = height
        back.opacity = 0

        back.startAnimation()

        back.x = x
        back.y = y
        back.opacity = 1
    }

    function hide(){
        back.startAnimation()

        back.x = back.x - extraX
        back.y = back.mirror? back.y + extraY : back.y - extraY
        back.opacity = 0
    }

    Component.onDestruction: BackHandler.removeHandler(p_dialog)
}
