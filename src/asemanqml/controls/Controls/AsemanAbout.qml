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

Rectangle {
    id: aseman_splash
    color: Desktop.titleBarColor

    property alias backButtonScale: header.backScale
    readonly property bool darkBackground: color.r<0.4 && color.g<0.4 && color.b<0.4
    property color textsColor: darkBackground? "#ffffff" : "#333333"
    property color highlightColor: "#0d80ec"
    property alias headerColor: header.color


    AsemanFlickable {
        id: flick
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: homeBtn.top
        contentHeight: item.height
        contentWidth: item.width
        clip: true

        Item {
            id: item
            width: flick.width
            height: column.height+40*Devices.density>flick.height? column.height+40*Devices.density : flick.height

            Column {
                id: column
                width: parent.width
                anchors.centerIn: parent
                spacing: 8*Devices.density

                Image {
                    id: logo
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 200*Devices.density
                    height: 142*Devices.density
                    sourceSize: Qt.size(width,height)
                    source: darkBackground? "files/aseman-special.png" : "files/aseman-special-black.png"
                    z: 10
                }

                Text {
                    id: desc_txt
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 20*Devices.density
                    anchors.rightMargin: 20*Devices.density
                    font.family: AsemanApp.globalFont.family
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    font.pixelSize: Math.floor(9*Devices.fontDensity)
                    color: textsColor
                    horizontalAlignment: Text.AlignHCenter
                    z: 10
                    text: qsTr("Aseman is a non-profit organization, exists to support and lead the free, open source and cross-platform projects and researches.")
                }

                Text {
                    id: goal_txt
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 20*Devices.density
                    anchors.rightMargin: 20*Devices.density
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    font.pixelSize: Math.floor(9*Devices.fontDensity)
                    font.family: AsemanApp.globalFont.family
                    color: textsColor
                    horizontalAlignment: Text.AlignHCenter
                    z: 10
                    text: qsTr("The Goal of the Aseman is to provide free and secure products to keep people’s freedom and their privacy.")
                }
            }
        }
    }

    Button {
        id: homeBtn
        anchors.bottom: parent.bottom
        anchors.bottomMargin: View.navigationBarHeight + 10*Devices.density
        anchors.horizontalCenter: parent.horizontalCenter
        height: 40*Devices.density
        width: 120*Devices.density
        normalColor: aseman_splash.highlightColor
        highlightColor: Qt.darker(masterPalette.highlight)
        textColor: "#ffffff"
        radius: 4*Devices.density
        text: qsTr("Home Page")
        onClicked: Qt.openUrlExternally("http://aseman.io")
    }

    Header {
        id: header
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        backButton: false
        color: aseman_splash.highlightColor
        light: darkBackground
    }
}
