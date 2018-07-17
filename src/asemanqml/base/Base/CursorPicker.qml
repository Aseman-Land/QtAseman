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

Item {
    id: cursor_picker
    width: 100
    height: 100
    visible: false
    opacity: 0

    property real pickerWidth: 35*Devices.density
    property real pickerHeight: 35*Devices.density

    property bool moving: false
    property bool press: top_handler.press || bottom_handler.press
    property bool commitBlocker: false
    property bool pickersVisible: top_picker.visible || bottom_picker.visible

    property color pickersColor: "#333333"
    property color pickersStrokeColor: "#000000"

    property variant textItem

    property int cursorPosition: textItem? textItem.cursorPosition : 0

    onTextItemChanged: {
        top_picker.visible = false
        bottom_picker.visible = false
        if(View.root)
            View.root.hideRollerDialog()
    }
    onCursorPositionChanged: {
        if( moving )
            return

        hide()
    }

    Behavior on opacity {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
    }

    Item{
        id: fader_item
        height: 60*Devices.density
        visible: false

        Button {
            id: copy_btn
            anchors.bottom: fader_item.bottom
            anchors.left: fader_item.left
            anchors.margins: 10*Devices.density
            width: (fader_item.width - 50*Devices.density)/4
            normalColor: "#ffffff"
            textColor: "#333333"
            onClicked: {
                Devices.clipboard = cursor_picker.selectedText()
                textItem.deselect()
                cursor_picker.hide()
            }
        }

        Button {
            id: cut_btn
            anchors.bottom: fader_item.bottom
            anchors.right: fader_item.horizontalCenter
            anchors.rightMargin: 5*Devices.density
            anchors.margins: 10*Devices.density
            width: (fader_item.width - 50*Devices.density)/4
            normalColor: "#ffffff"
            textColor: "#333333"
            onClicked: {
                Devices.clipboard = cursor_picker.selectedText()
                cursor_picker.deleteSelectedText()
                cursor_picker.hide()
            }
        }

        Button {
            id: paste_btn
            anchors.bottom: fader_item.bottom
            anchors.left: fader_item.horizontalCenter
            anchors.leftMargin: 5*Devices.density
            anchors.margins: 10*Devices.density
            width: (fader_item.width - 50*Devices.density)/4
            normalColor: "#ffffff"
            textColor: "#333333"
            onClicked: {
                var tmp = textItem
                cursor_picker.deleteSelectedText()
                tmp.insert( tmp.cursorPosition, Devices.clipboard )
                cursor_picker.hide()
            }
        }

        Button {
            id: delete_btn
            anchors.bottom: fader_item.bottom
            anchors.right: fader_item.right
            anchors.margins: 10*Devices.density
            width: (fader_item.width - 50*Devices.density)/4
            normalColor: "#aaC80000"
            textColor: "#ffffff"
            onClicked: {
                cursor_picker.deleteSelectedText()
                cursor_picker.hide()
            }
        }
    }

    Picker {
        id: bottom_picker
        width: pickerWidth
        height: pickerHeight
        opacity: disabled? 0.2 : 1.0
        fillColor: pickersColor
        strokeColor: pickersStrokeColor

        property bool disabled: true
    }

    Picker {
        id: top_picker
        width: pickerWidth
        height: pickerHeight
        opacity: disabled? 0.5 : 1.0
        fillColor: pickersColor
        strokeColor: pickersStrokeColor
        onVisibleChanged: {
            pasteButton.textItem = visible? cursor_picker.textItem : 0
        }

        property bool disabled: true
    }

    PickerHandler {
        id: bottom_handler
        width: pickerWidth
        height: pickerHeight*3/2
        onCommited: {
            cursor_picker.moving = false
            cursor_picker.commited(bottom_handler)
            bottom_picker.x = bottom_handler.x
            bottom_picker.y = bottom_handler.y
        }
        onMoved: {
            cursor_picker.moving = true
            commitBlocker = false
            bottom_picker.disabled = false
            View.root.hideRollerDialog()
            bottom_picker.x = bottom_handler.x
            bottom_picker.y = bottom_handler.y
            cursor_picker.calculateSelection()
        }
    }

    PickerHandler {
        id: top_handler
        width: pickerWidth
        height: pickerHeight*3/2
        onCommited: {
            cursor_picker.moving = false
            cursor_picker.commited(top_handler)
            top_picker.x = top_handler.x
            top_picker.y = top_handler.y
        }
        onMoved: {
            cursor_picker.moving = true
            commitBlocker = false
            top_picker.disabled = false
            View.root.hideRollerDialog()
            top_picker.x = top_handler.x
            top_picker.y = top_handler.y
            cursor_picker.calculateSelection()
            pasteButton.textItem = 0
        }
    }

    Timer {
        id: visible_timer
        interval: 250
        repeat: false
        onTriggered: refresh()
    }

    function isPointOnPickers( x, y ) {
        if( top_handler.x < x && x < top_handler.x+top_handler.width &&
            top_handler.y < y && y < top_handler.y+top_handler.height)
            return true
        else
        if( bottom_handler.x < x && x < bottom_handler.x+bottom_handler.width &&
            bottom_handler.y < y && y < bottom_handler.y+bottom_handler.height)
            return true
        else
            return false
    }

    function refresh(){
        if( !textItem )
        {
            cursor_picker.visible = false
            cursor_picker.opacity = 0
            bottom_picker.disabled = true
            top_picker.disabled = true
            View.root.hideRollerDialog()
            return
        }

        var trect = textItem.positionToRectangle( textItem.selectionStart )
        var tpx = trect.x + trect.width/2
        var tpy = trect.y + trect.height

        var brect = textItem.positionToRectangle( textItem.selectionEnd )
        var bpx = brect.x + brect.width/2
        var bpy = brect.y + brect.height

        var top_pos = mapFromItem( textItem, tpx, tpy )
        var btm_pos = mapFromItem( textItem, bpx, bpy )

        var select_mode = (textItem.selectionStart !== textItem.selectionEnd )

        top_handler.x = top_pos.x - top_handler.width/2
        top_handler.y = top_pos.y - 1
        top_picker.x = top_handler.x
        top_picker.y = top_handler.y
        top_picker.visible = true

        bottom_handler.x = btm_pos.x - bottom_handler.width/2
        bottom_handler.y = btm_pos.y - 1
        bottom_picker.x = bottom_handler.x
        bottom_picker.y = bottom_handler.y
        bottom_picker.visible = true

        cursor_picker.visible = true
        cursor_picker.opacity = 1
        bottom_picker.disabled = !select_mode
        top_picker.disabled = !select_mode

        if( select_mode )
            commitFaders()
        else
            View.root.hideRollerDialog()
    }

    function commited( item ){
        commitedTwo(item,item)
    }

    function commitedTwo( item, baseItem ){
        var crs_pos = getItemPosition(baseItem)
        var rect = textItem.positionToRectangle( crs_pos )

        var px = rect.x + rect.width/2
        var py = rect.y + rect.height

        var ps = cursor_picker.mapFromItem( textItem, px, py )

        item.x = ps.x - item.width/2
        item.y = ps.y - 1

        commitFaders()
        return crs_pos
    }

    function hide(){
        top_picker.visible = false
        bottom_picker.visible = false
        View.root.hideRollerDialog()
    }

    function show() {
        View.root.hideRollerDialog()
        visible_timer.restart()
    }

    function commitFaders(){
        if( commitBlocker )
            return

        var first_pos = top_handler.y
        var secnd_pos = bottom_handler.y

        if( first_pos > secnd_pos )
        {
            var tmp = first_pos
            first_pos = secnd_pos
            secnd_pos = tmp
        }

        first_pos -= 40*Devices.density
        secnd_pos += 30*Devices.density

        if( !bottom_picker.disabled )
            View.root.showRollerDialog( mapToItem(View.root,0,first_pos).y, mapToItem(View.root,0,secnd_pos).y, fader_item )
    }

    function getItemPosition( item ){
        var pos = item.mapToItem( textItem, item.width/2, 0 )
        var crs_pos = textItem.positionAt( pos.x, pos.y )
        return crs_pos
    }

    function calculateSelection(){
        var first_pos = getItemPosition(top_handler)
        var secnd_pos = getItemPosition(bottom_handler)

        if( bottom_picker.disabled )
        {
            textItem.cursorPosition = first_pos
            return
        }

        if( first_pos > secnd_pos )
            textItem.select( secnd_pos, first_pos )
        else
            textItem.select( first_pos, secnd_pos )
    }

    function selectedText(){
        var first_pos = getItemPosition(top_handler)
        var secnd_pos = getItemPosition(bottom_handler)

        if( first_pos > secnd_pos )
            return textItem.getText( secnd_pos, first_pos )
        else
            return textItem.getText( first_pos, secnd_pos )
    }

    function deleteSelectedText(){
        var first_pos = getItemPosition(top_handler)
        var secnd_pos = getItemPosition(bottom_handler)

        if( first_pos > secnd_pos )
            return textItem.remove( secnd_pos, first_pos )
        else
            return textItem.remove( first_pos, secnd_pos )
    }

    function declareSelectedText(){

    }

    function initTranslations(){
        copy_btn.text = qsTr("Copy")
        cut_btn.text = qsTr("Cut")
        paste_btn.text = qsTr("Paste")
        delete_btn.text = qsTr("Delete")
    }

    Component.onCompleted: initTranslations()
}
