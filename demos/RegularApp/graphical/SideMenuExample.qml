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
import AsemanQml.Controls 2.0
import "../global"

Rectangle {
    color: masterPalette.window

    MainPage {
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("SideMenu")
        shadow: true
    }

    SideMenu {
        id: sidebar
        anchors.fill: parent
        delegate: MouseArea {
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                color: "#f0f0f0"
            }
        }
    }

    HeaderMenuButton {
        ratio: sidebar.percent
        buttonColor: Qt.rgba(1-ratio, 1-ratio, 1-ratio, 1)
        onClicked: {
            if(sidebar.showed)
                sidebar.discard()
            else
                sidebar.show()
        }
    }
}
