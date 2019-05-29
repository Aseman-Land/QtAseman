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
    id: menu_icon
    height: 20*Devices.density
    width: height

    property color color: "#ffffff"
    property real ratio: 0

    property int layoutDirection: View.layoutDirection

    Column {
        width: Math.min(parent.width, parent.height)
        anchors.centerIn: parent
        spacing: 3*Devices.density
        rotation: ratio*180
        transform: Scale {
            origin.x: width/2
            origin.y: height/2
            xScale: (layoutDirection==Qt.LeftToRight?1:-1)*yScale
            yScale: 1-ratio/6
        }

        Rectangle {
            x: parent.width - width + ratio*parent.width*0.1
            width: (1-ratio)*parent.width*0.25 + parent.width*0.75
            height: 2*Devices.density
            radius: height/2
            color: menu_icon.color
            rotation: ratio*45
        }

        Rectangle {
            x: parent.width - width
            width: parent.width + ratio*parent.width*0.2
            height: 2*Devices.density
            radius: height/2
            color: menu_icon.color
        }

        Rectangle {
            x: parent.width - width + ratio*parent.width*0.1
            width: (1-ratio)*parent.width*0.25 + parent.width*0.75
            height: 2*Devices.density
            radius: height/2
            color: menu_icon.color
            rotation: -ratio*45
        }
    }
}
