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
    id: picker_handler
    width: 100
    height: 62

    property alias press: marea.pressed

    onPressChanged: {
        if( !press )
            commited()
    }

    signal commited()
    signal moved()

    MouseArea {
        id: marea
        anchors.fill: parent
        onMouseXChanged: {
            picker_handler.x += mouseX - last_x
            picker_handler.moved()
        }
        onMouseYChanged: {
            picker_handler.y += mouseY - last_y
            picker_handler.moved()
        }
        onPressed: {
            last_x = width/2
            last_y = height
        }

        property real last_x
        property real last_y
    }
}
