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

import QtQuick 2.7
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import "../global"

Rectangle {
    color: masterPalette.highlight

    Rectangle {
        id: rect
        color: masterPalette.window
        anchors.fill: parent

        MainPage {
            width: parent.width
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
        }

        Header {
            id: header
            width: parent.width
            color: masterPalette.highlight
            text: qsTr("MenuController")
            shadow: true
        }
    }

    MenuController {
        id: menuController
        anchors.fill: parent
        source: rect
        component: Item {
            anchors.fill: parent

            ListView {
                id: view
                model: 5
                width: parent.width - 40*Devices.density
                height: parent.height - 300*Devices.density
                anchors.centerIn: parent
                delegate: Item {
                    width: view.width
                    height: 40*Devices.density
                    Text {
                        x: View.layoutDirection==Qt.LeftToRight? 20*Devices.density : parent.width - width - 10*Devices.density
                        text: "Item " + index
                        color: "#ffffff"
                    }
                }
            }
        }
    }

    HeaderMenuButton {
        ratio: menuController.ratio
        buttonColor: "white"
        onClicked: {
            if(menuController.isVisible)
                menuController.close()
            else
                menuController.show()
        }
    }
}
