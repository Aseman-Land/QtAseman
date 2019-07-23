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

import QtQuick 2.9
import AsemanQml.Base 2.0

Item {
    id: indicator
    width: indicatorSize
    height: indicatorSize

    property bool light: true
    property bool modern: false
    property real indicatorSize: 16*Devices.density
    property string source: light? "files/" + privates.name + "_light.png" : "files/" + privates.name + ".png"

    property bool running: false

    onRunningChanged: {
        if(running)
            start()
        else
            stop()
    }

    QtObject {
        id: privates
        property variant item
        property string modern_name: "indicator_2"
        property string old_name: "indicator"
        property string name: modern? modern_name : old_name
    }

    Component {
        id: img_indicator
        Image {
            id: indict_img
            width: indicator.indicatorSize
            height: width
            anchors.centerIn: parent
            source: indicator.source
            sourceSize: Qt.size(width,height)
            smooth: true
            transformOrigin: Item.Center

            Behavior on rotation {
                NumberAnimation{ easing.type: Easing.Linear; duration: indict_img_timer.interval }
            }

            Timer {
                id: indict_img_timer
                interval: 250
                repeat: true
                triggeredOnStart: true
                onTriggered: indict_img.rotation += 90
                Component.onCompleted: start()
            }
        }
    }

    function start() {
        if( privates.item )
            return

        privates.item = img_indicator.createObject(indicator)
    }

    function stop() {
        if( !privates.item )
            return

        privates.item.destroy()
        privates.item = 0
    }
}
