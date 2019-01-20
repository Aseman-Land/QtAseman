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
    id: hmb
    width: height
    height: Devices.standardTitleBarHeight
    y: View.statusBarHeight
    x: View.layoutDirection==Qt.LeftToRight? 0 : parent.width - width

    property alias color: rect.color
    property alias buttonColor: menuIcon.color

    property alias ratio: menuIcon.ratio
    property alias pressed: marea.pressed

    signal clicked()

    Rectangle {
        id: rect
        anchors.fill: parent
        anchors.margins: 10*Devices.density
        color: menuIcon.color
        radius: 3*Devices.density
        opacity: pressed? 0.2 : 0
    }

    MenuIcon {
        id: menuIcon
        anchors.centerIn: parent
        layoutDirection: View.layoutDirection
    }

    MouseArea {
        id: marea
        anchors.fill: parent
        onClicked: hmb.clicked()
    }
}
