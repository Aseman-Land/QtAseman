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
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

Item {
    id: gbDialog
    anchors.fill: parent

    property color color: "#fefefe"
    property alias text: label.text
    property alias textColor: label.color
    property alias font: label.font
    property bool blockBack: false
    property alias scene: scene_prv

    NullMouseArea { anchors.fill: parent }

    Rectangle {
        anchors.fill: parent
        opacity: 0.4
        color: {
            var c = gbDialog.color
            if( (c.r + c.g + c.b)/3 < 0.5 )
                return "#ffffff"
            else
                return "#000000"
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
        width: scene_prv.width + 60*Devices.density
        height: scene_prv.height + 60*Devices.density
        anchors.centerIn: parent

        Rectangle {
            id: scene_prv
            color: gbDialog.color
            anchors.centerIn: parent
            width: row.width + 40*Devices.density
            height: row.height + 40*Devices.density
            radius: 3*Devices.density

            Row {
                id: row
                anchors.centerIn: parent
                spacing: 8*Devices.density

                BusyIndicator {
                    running: true
                    height: 48*Devices.density
                    width: height
                    anchors.verticalCenter: parent.verticalCenter
                }

                Label {
                    id: label
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }

    Component.onCompleted: {
        BackHandler.pushHandler(this, function(){
            if(blockBack)
                return false
            else
                BackHandler.back()
        })
    }
}
