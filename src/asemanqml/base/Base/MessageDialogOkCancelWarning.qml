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

Column {
    id: column
    anchors.verticalCenter: parent.verticalCenter
    anchors.left: parent.left
    anchors.right: parent.right
    spacing: 10*Devices.density

    property alias message: msg.text
    property alias okText: okBtn.text

    signal canceled()
    signal ok()

    Item {width: 1; height: 1}

    Text {
        id: msg
        width: column.width - 60*Devices.density
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: AsemanApp.globalFont.family
        font.pixelSize: 9*Devices.fontDensity
        color: "#333333"
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    Row {
        anchors.right: parent.right
        anchors.rightMargin: 10*Devices.density

        Button {
            textFont.family: AsemanApp.globalFont.family
            textFont.pixelSize: 10*Devices.fontDensity
            textColor: "#0d80ec"
            normalColor: "#00000000"
            highlightColor: "#660d80ec"
            text: qsTr("Cancel")
            radius: 3*Devices.density
            onClicked: {
                column.canceled()
                AsemanApp.back()
            }
        }

        Button {
            id: okBtn
            textFont.family: AsemanApp.globalFont.family
            textFont.pixelSize: 10*Devices.fontDensity
            textColor: "#0d80ec"
            normalColor: "#00000000"
            highlightColor: "#660d80ec"
            text: qsTr("OK")
            radius: 3*Devices.density
            onClicked: column.ok()
        }
    }
}
