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

Rectangle {
    id: header
    width: 100
    height: defaultHeight
    color: "#00000000"

    property alias text: title_txt.text
    property alias titleFont: title_txt.font
    property alias titleFontSize: title_txt.font.pixelSize
    property bool light: true
    property bool backButton: false
    property real backScale: 1
    property alias backButtonText: back_txt.text
    property alias shadow: shadow_rct.visible
    property alias shadowOpacity: shadow_rct.opacity
    property bool statusBar: Devices.transparentStatusBar
    property bool centerText: true
    property int layoutDirection: View.layoutDirection

    readonly property real defaultHeight: Devices.standardTitleBarHeight + (statusBar? View.statusBarHeight : 0)

    signal beginBack()

    Item {
        anchors.fill: parent
        anchors.topMargin: statusBar? View.statusBarHeight : 0

        Rectangle {
            id: shadow_rct
            height: 3*Devices.density
            width: parent.width
            anchors.top: parent.bottom
            visible: !Devices.isIOS
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#55000000" }
                GradientStop { position: 1.0; color: "#00000000" }
            }
        }

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 1*Devices.density
            visible: !shadow_rct.visible
            color: "#33000000"
        }

        Row {
            id: back_row
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10*Devices.density
            visible: backButton

            Image {
                anchors.verticalCenter: parent.verticalCenter
                height: 20*Devices.density*backScale
                source: header.light? (height>48? "files/back_light_64.png" : "files/back_light_32.png") : (height>48? "files/back_64.png" : "files/back_32.png")
                fillMode: Image.PreserveAspectFit
                smooth: true
                opacity: back_row.press? 0.6 : 0.8
            }

            Text {
                id: back_txt
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: Math.floor(12*Devices.fontDensity*backScale)
                font.family: AsemanApp.globalFont.family
                text: qsTr("Back")
                color: {
                    if(header.light) {
                        return back_row.press? "#dddddd" : "#ffffff"
                    } else {
                        return back_row.press? "#555555" : "#111111"
                    }
                }
            }

            property bool press: false
        }

        MouseArea {
            anchors.fill: back_row
            anchors.margins: -10*Devices.density
            onPressed: back_row.press = true
            onReleased: back_row.press = false
            visible: back_row.visible
            onClicked: {
                header.beginBack()
                BackHandler.back()
            }
        }

        Text {
            id: title_txt
            font.pixelSize: Math.floor(10*Devices.fontDensity)
            font.family: AsemanApp.globalFont.family
            y: Devices.standardTitleBarHeight/2 - height/2
            x: {
                if(centerText)
                    return parent.width/2 - width/2
                else
                if(layoutDirection == Qt.RightToLeft)
                    return parent.width - Devices.standardTitleBarHeight - width
                else
                    return Devices.standardTitleBarHeight
            }

            color: header.light? "#ffffff" : "#333333"
        }
    }

    Connections{
        target: AsemanApp
        onLanguageUpdated: initTranslations()
    }

    function initTranslations(){
        back_txt.text = qsTr("Back")
    }
}
