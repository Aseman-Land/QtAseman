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

Rectangle{
    width: 10*Devices.density
    height: width
    color: "#ffffff"
    anchors.verticalCenter: parent.verticalCenter
    x: (parent.width - parent.count*(width+space))/2 + index*(width+space) + x_pad

    property real space: 2*Devices.density
    property real x_pad: 0
    property int index: 0

    Behavior on x {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 337 }
    }

    function poke(){
        x_pad = -(count/2-index-1)*width - width/2
        revert_timer.start()
    }

    Timer{
        id:revert_timer
        interval: 250
        repeat: false
        onTriggered: x_pad = 0
    }
}
