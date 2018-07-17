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
import QtGraphicalEffects 1.0
import AsemanQml.Base 2.0

Item {
    property alias color : back.color
    property alias radius: back.radius
    property alias border: back.border
    property alias shadowOpacity: blur.opacity
    property real shadowSize: shadowRadius
    property alias shadowRadius: blur.radius
    property alias visibleShadow: blur.visible

    Item {
        id: shadow
        anchors.fill: parent
        visible: false

        Rectangle {
            anchors.centerIn: parent
            width: back.width
            height: back.height
            radius: back.radius
            color: "#333333"
        }
    }

    FastBlur {
        id: blur
        anchors.fill: shadow
        source: shadow
        radius: 16*Devices.density
        opacity: 0.8
    }

    Rectangle {
        id: back
        anchors.fill: parent
        anchors.margins: shadowSize
    }
}
