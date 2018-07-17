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
    id: line_edit_frame
    color: "#88eeeeee"
    height: 42*Devices.density
    width: 100*Devices.density

    property alias placeholder: pholder.text
    property alias placeholderColor: pholder.color
    property alias text: main_item.text
    property alias textColor: main_item.color
    property alias font: main_item.font
    property alias echoMode: main_item.echoMode
    property alias lineFocus: main_item.focus
    property alias pickerEnable: main_item.pickerEnable
    property alias validator: main_item.validator
    property real textSideMargins: 4*Devices.density
    property bool clearButton: false

    signal accepted()

    Text {
        id: pholder
        anchors.fill: main_item
        font: main_item.font
        color: "#888888"
        visible: main_item.length == 0
        verticalAlignment: Text.AlignVCenter
    }

    TextLineCore {
        id: main_item
        anchors.fill: parent
        anchors.margins: 4*Devices.density
        anchors.leftMargin: textSideMargins
        anchors.rightMargin: textSideMargins
        font.pixelSize: Math.floor(11*Devices.fontDensity)
        font.family: AsemanApp.globalFont.family
        color: "#333333"
        verticalAlignment: Text.AlignVCenter
        onAccepted: line_edit_frame.accepted()
    }

    Button {
        x: main_item.horizontalAlignment==TextInput.AlignRight? 6*Devices.density : parent.width-6*Devices.density-width
        anchors.verticalCenter: parent.verticalCenter
        width: 18*Devices.density
        height: width
        normalColor: "#88000000"
        highlightColor: "#44000000"
        icon: "files/close.png"
        iconHeight: 12*Devices.density
        radius: parent.radius
        visible: main_item.text.length != 0 && clearButton
        cursorShape: Qt.PointingHandCursor
        onClicked: main_item.text = ""
    }

    function paste() {
        main_item.paste()
    }

    function copy() {
        main_item.copy()
    }

    function cut() {
        main_item.cut()
    }
}
