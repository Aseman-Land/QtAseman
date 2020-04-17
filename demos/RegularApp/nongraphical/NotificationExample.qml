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
import AsemanQml.Widgets 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Item {

    Notification {
        id: notification
    }

    Item {
        id: listv
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom

        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 20*Devices.density

            TextField {
                id: titleTxt
                placeholderText: qsTr("Title")
                Layout.fillWidth: true
            }

            TextArea {
                id: body
                placeholderText: qsTr("Body text")
                Layout.fillWidth: true
                Layout.preferredHeight: 200*Devices.density
            }

            Button {
                text: "Send"
                Layout.fillWidth: true
                Material.foreground: Material.LightBlue
                onClicked: notification.sendNotify(titleTxt.text, body.text, "")
            }
        }
    }

    Header {
        id: header
        width: parent.width
        color: "#18f"
        text: qsTr("Notification")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }
}
