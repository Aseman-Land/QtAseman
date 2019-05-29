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

Item {
    id: tooltip
    width: tooltipScene.width
    height: tooltipScene.height

    property int interval: 1500
    property real padding: 8*Devices.density

    property alias textFont: txt.font
    property alias textColor: txt.color
    property alias color: tooltipRect.color

    Item {
        id: tooltipScene
        width: tooltipRect.width + 32*Devices.density
        height: tooltipRect.height + 32*Devices.density
        anchors.centerIn: parent
        visible: opacity != 0
        opacity: 0

        Behavior on opacity {
            NumberAnimation { id: anim_item; easing.type: Easing.OutCubic; duration: 250 }
        }

        Rectangle {
            id: tooltipRect
            width: txt.width + padding*2
            height: txt.height + padding*1.5
            anchors.centerIn: parent
            radius: 3*Devices.density
            color: "#fefefe"

            Text {
                id: txt
                anchors.centerIn: parent
                font.pixelSize: 10*Devices.fontDensity
                font.family: AsemanApp.globalFont.family
                color: "#333"
            }
        }
    }

    Timer{
        id: hide_timer
        interval: tooltip.interval + 250
        repeat: false
        onTriggered: tooltipScene.opacity = 0
    }

    function showText( text ){
        txt.text = text
        tooltipScene.opacity = 0.9
        hide_timer.restart()
    }
}
