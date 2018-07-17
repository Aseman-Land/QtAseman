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
import AsemanTools 1.0
import QtQuick.Controls 2.0

Item {

    Item {
        id: listv
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom

        Column {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 20*Devices.density

            Repeater {
                model: 5
                CheckBox {
                    id: checkBox
                    text: "Check " + index
                    onCheckedChanged: {
                        if(checked)
                            BackHandler.pushHandler(checkBox, function(){checkBox.checked = false})
                        else
                            BackHandler.removeHandler(checkBox)
                    }
                }
            }
        }
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("BackHandler")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }
}
