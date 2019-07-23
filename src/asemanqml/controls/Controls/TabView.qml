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
    width: 100
    height: 62

    property alias model: tabs_list.model
    property real minimumTabSize: 40*Devices.density
    property real maximumTabSize: width - 40*Devices.density
    property real tabsHeight: 50*Devices.density

    property alias currentIndex: tabs_list.currentIndex

    AsemanListView {
        id: tabs_list
        width: parent.width
        height: tabsHeight
        orientation: ListView.Horizontal
        currentIndex: 0
        delegate: Item {
            clip: true
            height: tabs_list.height
            width: {
                var result = tabs_list.width/tabs_list.count
                if(result < minimumTabSize)
                    result = minimumTabSize
                if(result > maximumTabSize)
                    result = maximumTabSize
                return result
            }

            Text {
                anchors.centerIn: parent
                text: model.text
                font.pixelSize: 13*Devices.fontDensity
                color: "#ffffff"
            }
        }
        highlight: Item {
            clip: true
            height: tabs_list.height
            width: {
                var result = tabs_list.width/tabs_list.count
                if(result < minimumTabSize)
                    result = minimumTabSize
                if(result > maximumTabSize)
                    result = maximumTabSize
                return result
            }

            Rectangle {
                anchors.verticalCenter: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                width: 16*Devices.density
                height: width
                rotation: 45
                transformOrigin: Item.Center
            }
        }
    }

    Rectangle {
        width: parent.width
        anchors.top: tabs_list.bottom
        anchors.bottom: parent.bottom
    }
}
