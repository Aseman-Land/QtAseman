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

Item {
    id: item
    width: parent.width
    height: 50*Devices.density

    property alias text: txt.text

    signal clicked()

    Rectangle {
        anchors.fill: parent
        color: masterPalette.highlight
        opacity: marea.pressed? 0.3 : 0
        Behavior on opacity {
            NumberAnimation{easing.type: Easing.OutCubic; duration: 400}
        }
    }

    Text {
        id: txt
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 10*Devices.fontDensity
        x: View.layoutDirection==Qt.LeftToRight? 20*Devices.density : parent.width - width - 10*Devices.density
    }

    MouseArea {
        id: marea
        anchors.fill: parent
        onClicked: item.clicked()
    }

    Rectangle {
        width: parent.width
        anchors.bottom: parent.bottom
        height: 1
        color: "#cccccc"
    }
}
