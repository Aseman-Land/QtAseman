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
    id: header
    width: 100
    height: defaultHeight
    color: "#00000000"

    property alias text: title_txt.text
    property alias titleFont: title_txt.font
    property alias titleFontSize: title_txt.font.pixelSize
    property bool light: true
    property alias shadow: shadow_rct.visible
    property alias shadowOpacity: shadow_rct.opacity
    property bool statusBar: Devices.transparentStatusBar
    property bool centerText: true

    readonly property real defaultHeight: Devices.standardTitleBarHeight + (statusBar? View.statusBarHeight : 0)

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
            opacity: shadow_rct.opacity
            color: "#33000000"
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
                if(LayoutMirroring.enabled)
                    return parent.width - Devices.standardTitleBarHeight - width
                else
                    return Devices.standardTitleBarHeight
            }

            color: header.light? "#ffffff" : "#333333"
        }
    }
}
