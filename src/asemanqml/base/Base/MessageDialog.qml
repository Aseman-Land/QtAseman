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
    id: mdialog
    width: 100
    height: 62

    property variant frameItem

    onFrameItemChanged: {
        if( frameItem )
            BackHandler.pushHandler(mdialog, mdialog.hide)
        else
            BackHandler.removeHandler(mdialog)
    }

    MouseArea {
        anchors.fill: parent
        visible: frameItem? true : false
        onClicked: BackHandler.back()
    }

    Rectangle {
        opacity: frameItem? 0.5 : 0
        anchors.fill: parent
        color: "#000000"

        Behavior on opacity {
            NumberAnimation{ easing.type: Easing.OutCubic; duration: 400 }
        }
    }

    Component {
        id: msg_dialog
        Rectangle {
            id: msg_f_item
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 10*Devices.density
            height: item? item.height + 20*Devices.density : 0
            radius: 3*Devices.density
            transformOrigin: Item.Center
            scale: 0.8
            opacity: (scale-0.8)*5

            Behavior on scale {
                NumberAnimation{ easing.type: Easing.OutCubic; duration: 400 }
            }

            MouseArea {
                anchors.fill: parent
            }

            property variant item

            onItemChanged: if(item) item.width = msg_f_item.width
            onWidthChanged: if(item) item.width = msg_f_item.width

            Timer {
                id: destroy_timer
                interval: 400
                onTriggered: {
                    msg_f_item.item.destroy()
                    msg_f_item.destroy()
                }
            }

            function end() {
                scale = 0.8
                destroy_timer.restart()
            }
        }
    }

    function show( component, args ) {
        if( frameItem )
            return

        frameItem = msg_dialog.createObject(mdialog)
        frameItem.item = args? component.createObject(frameItem, args) :
                               component.createObject(frameItem)
        frameItem.scale = 1
    }

    function hide() {
        if( !frameItem )
            return

        frameItem.end()
        frameItem = 0
    }
}
