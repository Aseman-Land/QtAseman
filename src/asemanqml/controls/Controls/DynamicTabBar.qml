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
import QtQuick.Controls 2.0 as QtControls

Item {
    id: tbar
    height: 50*Devices.density

    property alias color: back.color
    property real minimumWidth: 120*Devices.density
    property alias model: tabBar.model
    property alias currentIndex: tabBar.currentIndex
    property color highlightColor: "#03A9F4"
    property color textColor: "#333333"
    property real fontSize: 12*Devices.fontDensity
    property string fontFamily: AsemanApp.globalFont.family
    property string displayRole

    signal clicked(int index)

    Rectangle {
        id: back
        anchors.fill: tabBar
    }

    AsemanListView {
        id: tabBar
        anchors.fill: parent
        orientation: Qt.Horizontal

        delegate: QtControls.ItemDelegate {
            height: tabBar.height
            width: {
                var res = tabBar.width/tabBar.count
                if(res < minimumWidth)
                    res = minimumWidth
                return res
            }
            hoverEnabled: false
            onClicked: {
                tabBar.currentIndex = index
                tbar.clicked(model.index)
            }

            Text {
                width: parent.width
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAnywhere
                maximumLineCount: 1
                elide: Text.ElideRight
                font.pixelSize: fontSize
                font.family: tbar.fontFamily
                color: tabBar.currentIndex==index? highlightColor : textColor
                text: displayRole.length? model[displayRole] : tabBar.model[index]
            }
        }
        highlightMoveDuration: 400
        highlight: Item {
            height: tabBar.height
            width: tabBar.itemWidth

            Rectangle {
                width: parent.width
                height: 3*Devices.density
                anchors.bottom: parent.bottom
                color: highlightColor
            }
        }
    }
}
