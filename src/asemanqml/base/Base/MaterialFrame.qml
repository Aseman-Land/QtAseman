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

import AsemanQml.Base 2.0
import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {

    property alias color: backFrame.color
    property alias radius: backFrame.radius
    property alias shadowColor: shadow.color

    DropShadow {
        id: shadow
        anchors.fill: source
        cached: true
        horizontalOffset: 1*Devices.density
        verticalOffset: 1*Devices.density
        radius: 6*Devices.density
        samples: 16
        color: "#000000"
        source: scene
        opacity: 0.3
        visible: !Devices.isIOS
    }

    Item {
        id: scene
        anchors.fill: parent
        anchors.margins: -5*Devices.density

        Rectangle {
            id: backFrame
            anchors.fill: parent
            anchors.margins: 5*Devices.density
            radius: 3*Devices.density
        }
    }
}
