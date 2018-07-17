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
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Rectangle {
    color: analizer.color!="#000000"? analizer.color : "#ffffff"

    property variant encryptedData: null

    Behavior on color {
        ColorAnimation { easing.type: Easing.OutCubic; duration: 1000 }
    }

    ImageColorAnalizor {
        id: analizer
        method: algorithm.currentIndex
    }

    Connections {
        target: Devices
        onSelectImageResult: analizer.source = Devices.localFilesPrePath + path
    }

    Item {
        id: listv
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom

        ColumnLayout {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 20*Devices.density

            Label {
                text: "Algorithm:"
                Layout.fillWidth: true
                font.bold: true
            }

            ComboBox {
                id: algorithm
                Layout.fillWidth: true
                model: ["Normal", "Saturation"]
            }

            Button {
                text: "Select Image"
                Layout.fillWidth: true
                Material.foreground: Material.LightBlue
                onClicked: Devices.getOpenPictures()
            }
        }

        Image {
            anchors.top: column.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20*Devices.density
            verticalAlignment: Image.AlignTop
            horizontalAlignment: Image.AlignHCenter
            fillMode: Image.PreserveAspectFit
            source: analizer.source
        }
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("ImageColorAnalizor")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }
}
