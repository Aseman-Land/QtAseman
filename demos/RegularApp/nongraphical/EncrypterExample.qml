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
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Item {

    property variant encryptedData: null

    Encrypter {
        id: encrypter
        key: keyTxt.text
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
                id: keyTxt
                placeholderText: qsTr("Encrypt Key")
                Layout.fillWidth: true
            }

            TextArea {
                id: txt
                Layout.fillWidth: true
                Layout.preferredHeight: 200*Devices.density
                enabled: encryptedData == null
            }

            Button {
                text: encryptedData? "Decrypt" : "Encrypt"
                Layout.fillWidth: true
                Material.foreground: Material.LightBlue
                onClicked: {
                    if(encryptedData) {
                        var data = encrypter.decrypt(encryptedData)
                        if(data == "") {
                            txt.color = "#ff0000"
                            txt.text = "No valid key"
                            return
                        }

                        txt.text = data
                        txt.color = "#000000"
                        encryptedData = null
                    } else {
                        encryptedData = encrypter.encrypt(txt.text)
                        txt.text = encryptedData
                    }
                }
            }
        }
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("Encrypter")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }
}
