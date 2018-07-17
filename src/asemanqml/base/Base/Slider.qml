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
    id: slider
    width: 100
    height: 30

    property real maximum: 100
    property real value: 0

    property alias backColor: back.color
    property alias backRadius: back.radius
    property alias backBorder: back.border
    property alias backHeight: back.height

    property alias seekerColor: seeker.color
    property alias seekerBorder: seeker.border

    property alias pressed: marea.pressed

    Rectangle {
        id: back
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height: 4*Devices.density
        color: "#ffffff"
    }

    Rectangle {
        id: seeker
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: height
        radius: height/2
        border.width: 1*Devices.density
        border.color: masterPalette.highlight
        x: (slider.width-seeker.width)*slider.value/slider.maximum
    }

    MouseArea {
        id: marea
        anchors.fill: parent
        onMouseXChanged: {
            var mx = mouseX - seeker.width/2
            var mw = slider.width - seeker.width

            if( mx < 0 )
                mx = 0
            if( mx > mw )
                mx = mw

            slider.value = slider.maximum * mx/mw
        }
        onPressed: mouse.accepted = true
    }
}
