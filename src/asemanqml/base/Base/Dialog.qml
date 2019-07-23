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
import QtGraphicalEffects 1.0

Item {
    id: gbDialog
    anchors.fill: parent
    visible: false

    property color color: "#fefefe"
    property alias title: label.text
    property alias textColor: label.color
    property alias font: label.font
    property bool blockBack: false
    property alias delegate: rptr.delegate

    property bool autoDestroy: false

    property variant buttons: new Array
    property real margins: 10*Devices.density

    signal buttonClicked(int index)

    property bool opened: false

    onVisibleChanged: {
        if(visible)
            BackHandler.pushHandler(this, function(){opened = false})
        else {
            BackHandler.removeHandler(this)
            if(autoDestroy)
                Tools.jsDelayCall(100, gbDialog.destroy)
        }
    }

    onOpenedChanged: {
        if(opened)
            visible = opened
        else
            Tools.jsDelayCall(200, function(){ visible = opened })
    }

    MouseArea {
        anchors.fill: parent
        onClicked: gbDialog.opened = false
    }

    Rectangle {
        anchors.fill: parent
        opacity: gbDialog.opened? 0.4 : 0
        color: {
            var c = gbDialog.color
            if( (c.r + c.g + c.b)/3 < 0.5 )
                return "#ffffff"
            else
                return "#000000"
        }

        Behavior on opacity {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }
    }

    DropShadow {
        anchors.fill: shadowSource
        horizontalOffset: 0
        verticalOffset: 5*Devices.density
        radius: 32*Devices.density
        samples: 32
        color: "#70000000"
        source: shadowSource
        cached: true
    }

    Item {
        id: shadowSource
        width: scene.width + 40*Devices.density
        height: scene.height + 40*Devices.density
        anchors.centerIn: parent

        Rectangle {
            id: scene
            color: gbDialog.color
            anchors.centerIn: parent
            width: row.width + gbDialog.margins
            height: row.height + gbDialog.margins
            radius: 3*Devices.density
            scale: 0.9 + opacity*0.1
            opacity: gbDialog.opened? 1 : 0

            Behavior on opacity {
                NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
            }

            Column {
                id: row
                anchors.centerIn: parent
                spacing: 8*Devices.density

                Text {
                    id: label
                    width: parent.width
                    font.pixelSize: 13*Devices.fontDensity
                    visible: text.length != 0
                }

                Repeater {
                    id: rptr
                    model: 1
                }

                Row {
                    width: parent.width
                    Repeater {
                        model: buttons
                        delegate: Button {
                            width: row.width/buttons.length
                            height: 42*Devices.density
                            normalColor: "#00000000"
                            textColor: gbDialog.textColor
                            highlightColor: "#22000000"
                            text: buttons[index]
                            fontSize: 9*Devices.fontDensity
                            onClicked: buttonClicked(index)
                        }
                    }
                }
            }
        }
    }

    function open() {
        opened = true
    }

    function close() {
        opened = false
    }
}
