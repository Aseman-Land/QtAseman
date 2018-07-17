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

Item {

    Downloader {
        id: downloader
        path: linkTxt.text
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
                id: linkTxt
                placeholderText: qsTr("Download Link: http://...")
                enabled: !downloader.downloading
                Layout.fillWidth: true
            }

            Button {
                text: downloader.downloading? "Stop" : "Download"
                Layout.fillWidth: true
                Material.foreground: Material.LightBlue
                onClicked: {
                    if(downloader.downloading)
                        downloader.stop()
                    else
                        downloader.start()
                }
            }

            Label {
                text: qsTr("Downloading to the RAM...\nTo download to memory, use destination property.")
                visible: downloader.downloading
            }

            ProgressBar {
                value: downloader.recievedBytes/downloader.totalBytes
                visible: downloader.downloading
                Layout.fillWidth: true
            }
        }
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("Downloader")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }
}
