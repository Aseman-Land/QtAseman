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

import QtQuick 2.0
import AsemanQml.Base 2.0
import QtGraphicalEffects 1.0
import AsemanQml.Awesome 2.0

Item {
    id: mdb_item
    width: row.width

    property alias buttonHeight: button_frame.height
    property alias text: txt.text
    property alias icon: img.source
    property alias iconText: icon_txt.text

    property alias layoutDirection: row.layoutDirection

    signal clicked()

    LayoutMirroring.enabled: false
    LayoutMirroring.childrenInherit: true

    Row {
        id: row
        height: parent.height
        layoutDirection: View.layoutDirection

        Rectangle {
            color: "#00ffffff"
            radius: 4*Devices.density
            width: txt.width + 12*Devices.density
            height: txt.height + 12*Devices.density
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id: txt
                anchors.centerIn: parent
                color: "#333333"
                font.pixelSize: 10*Devices.fontDensity
                font.bold: false
                font.family: AsemanApp.globalFont.family
            }
        }

        Item {
            id: button_frame
            width: height
            height: 64*Devices.density
            anchors.verticalCenter: parent.verticalCenter

            DropShadow {
                anchors.fill: btn_rect
                horizontalOffset: 0
                verticalOffset: 1
                radius: 8.0
                samples: 16
                color: "#66000000"
                cached: true
                source: btn_rect
                visible: !Devices.isIOS
            }

            Item {
                id: btn_rect
                anchors.fill: parent

                Behavior on y {
                    NumberAnimation{easing.type: Easing.OutCubic; duration: 400}
                }

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 8*Devices.density
                    color: "#ffffff"
                    radius: width/2

                    Behavior on color {
                        ColorAnimation{easing.type: Easing.OutCubic; duration: 400}
                    }
                }
            }

            Image {
                id: img
                anchors.fill: parent
                anchors.margins: 18*Devices.density
                fillMode: Image.PreserveAspectFit
                sourceSize: Qt.size(width, height)
            }

            Text {
                id: icon_txt
                anchors.centerIn: parent
                color: "#333333"
                font.family: Awesome.family
                font.pixelSize: 11*Devices.fontDensity
                font.bold: false
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: mdb_item.clicked()
    }
}
