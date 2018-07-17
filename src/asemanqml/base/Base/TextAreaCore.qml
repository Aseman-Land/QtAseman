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

STextEdit {
    id: core
    selectByMouse: !pickerEnable

    property alias press: cpicker.press
    property alias commitBlocker: cpicker.commitBlocker
    property alias pickersVisible: cpicker.pickersVisible
    property alias pickerEnable: marea.visible

    property alias placeholder: pholder.text
    property alias placeholderColor: pholder.color

    property alias pickersColor: cpicker.pickersColor
    property alias pickersStrokeColor: cpicker.pickersStrokeColor

    onTextChanged: {
        if( privates.last_text != text )
            cpicker.hide()

        privates.last_text = text
    }
    onFocusChanged: {
        if( !focus )
            cpicker.hide()
    }

    QtObject {
        id: privates
        property string last_text
    }

    Text {
        id: pholder
        anchors.fill: core
        font: core.font
        color: CutegramGlobals.baseColor
        visible: privates.last_text.length == 0
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.IBeamCursor
        visible: !marea.visible
        onPressed: mouse.accepted = false
    }

    MouseArea {
        id: marea
        anchors.fill: parent
        onPressed: {
            cpicker.show()
            if( core.selectionEnd == core.selectionStart )
                mouse.accepted = false
            else
                mouse.accepted = true
        }
        onReleased: {
            core.deselect()
            core.cursorPosition = core.positionAt(mouseX,mouseY)
        }
    }

    CursorPicker {
        id: cpicker
        anchors.fill: parent
        textItem: core
    }

    function isPointOnPickers( x, y ) {
        return cpicker.isPointOnPickers(x,y)
    }

    function commitFaders() {
        cpicker.commitFaders()
    }

    function showPicker() {
        cpicker.show()
    }

    function hidePicker() {
        cpicker.hide()
    }
}
