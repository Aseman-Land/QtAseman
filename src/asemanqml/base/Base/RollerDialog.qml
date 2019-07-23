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
    id: roller_dialog
    width: 100
    height: 100
    visible: false

    onVisibleChanged: {
        if( visible )
            BackHandler.pushHandler(roller_dialog,roller_dialog.hide)
        else
            BackHandler.removeHandler(roller_dialog)
    }

    Rectangle {
        id: top_fader
        anchors.left: roller_dialog.left
        anchors.right: roller_dialog.right
        anchors.top: roller_dialog.top
        anchors.margins: -1*Devices.density
        color: "#bb000000"
        height: size

        property real size: 0

        Behavior on height {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: roller_dialog.hide()
        }

        property variant item
        onItemChanged: {
            if( !item )
                return
            item.parent = top_fader
            item.visible = true
            item.x = 0
            item.y = height-item.height
            item.width = width
        }
        onHeightChanged: {
            if( !item )
                return
            item.y = height-item.height
        }
        onWidthChanged: {
            if( !item )
                return

            item.x = 0
            item.width = width
        }
    }

    Rectangle {
        id: bottom_fader
        anchors.left: roller_dialog.left
        anchors.right: roller_dialog.right
        anchors.bottom: roller_dialog.bottom
        anchors.margins: -1*Devices.density
        color: "#bb000000"
        height: (size != 0)? roller_dialog.height-size : 0

        property real size: 0

        Behavior on height {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: roller_dialog.hide()
        }

        property variant item
        onItemChanged: {
            if( !item )
                return
            item.parent = bottom_fader
            item.visible = true
            item.x = 0
            item.y = 0
            item.width = width
        }
        onHeightChanged: {
            if( !item )
                return
            item.y = 0
        }
        onWidthChanged: {
            if( !item )
                return

            item.x = 0
            item.width = width
        }
    }

    Timer {
        id: visible_timer
        interval: 250
        repeat: false
        onTriggered: {
            roller_dialog.visible = false
            top_fader.item = 0
            bottom_fader.item = 0
        }
    }

    function show( y1, y2, item ){
        hide()

        if( y1 > height-y2 ) {
            top_fader.item = item
            if( y1 < item.height )
                y1 = item.height
        } else {
            bottom_fader.item = item
            if( height-y2 < item.height )
                y2 = height-item.height
        }

        top_fader.size = y1
        bottom_fader.size = y2

        visible_timer.stop()
        roller_dialog.visible = true
    }

    function hide(){
        top_fader.size = 0
        bottom_fader.size = 0
        if( top_fader.item )
            top_fader.item.visible = false
        if( bottom_fader.item )
            bottom_fader.item.visible = false

        top_fader.item = 0
        bottom_fader.item = 0
        visible_timer.restart()
    }
}
