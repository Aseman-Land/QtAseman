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

AboutPageItem {
    title: qsTr("Aseman")
    icon: "files/aseman-abstract.png"
    color: "#0d80ec"
    delegate: Rectangle {
        id: about
        color: "#ffffff"

        AsemanFlickable {
            id: flickable
            width: parent.width
            anchors.top: parent.top
            anchors.bottom: home_btn.top
            anchors.bottomMargin: 4*Devices.density
            flickableDirection: Flickable.VerticalFlick
            clip: true

            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10*Devices.density

                Item { width: 1; height: 20*Devices.density }

                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: about.width*0.4
                    height: width
                    source: "files/aseman-silver-shadowed.png"
                    sourceSize: Qt.size(width*2, height*2)
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#333333"
                    font.family: AsemanApp.globalFont.family
                    font.pixelSize: 17*fontRatio*Devices.fontDensity
                    text: qsTr("Aseman Team")
                }

                Text {
                    width: about.width - 40*Devices.density
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#333333"
                    font.family: AsemanApp.globalFont.family
                    font.pixelSize: 9*Devices.fontDensity
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    text: qsTr("Aseman is a non-profit organization, exists to support and lead the free, open source and cross-platform projects and researches.")
                }

                Text {
                    width: about.width - 40*Devices.density
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#333333"
                    font.family: AsemanApp.globalFont.family
                    font.pixelSize: 9*Devices.fontDensity
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    text: qsTr("The Goal of the Aseman is to provide free and secure products to keep people’s freedom and their privacy.")
                }
            }
        }

        Button {
            id: home_btn
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10*Devices.density
            height: 36*Devices.density
            width: 150*Devices.density
            text: qsTr("Home")
            onClicked: Qt.openUrlExternally("http://aseman.co")
            normalColor: "#0d80ec"
            highlightColor: Qt.darker(normalColor, 1.1)
            textColor: "#ffffff"
            radius: 4*Devices.density
        }
    }
}
