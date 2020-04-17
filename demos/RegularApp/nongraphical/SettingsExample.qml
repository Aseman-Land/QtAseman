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
import QtQuick.Controls 2.0
import AsemanQml.Controls 2.0
import AsemanQml.Base 2.0

Item {

    Settings {
        id: settings
        source: AsemanApp.homePath + "/settings.ini"
        category: "General"

        property int number: 10
        property string text: "test Text"
    }

    Header {
        id: header
        width: parent.width
        color: "#18f"
        text: qsTr("Settings")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }

    Label {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.margins: 10*Devices.density
        text: "Every changes in this page will be saved."
    }

    Column {
        anchors.centerIn: parent

        SpinBox {
            anchors.horizontalCenter: parent.horizontalCenter
            value: settings.number
            onValueChanged: settings.number = value
        }

        TextField {
            anchors.horizontalCenter: parent.horizontalCenter
            text: settings.text
            onTextChanged: settings.text = text
        }
    }
}
