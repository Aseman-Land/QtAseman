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
import QtQuick.Controls 2.0 as QtControls
import QtGraphicalEffects 1.0
import QtQuick.Window 2.2
import AsemanQml.Awesome 2.0

Item {
    id: tcarea
    anchors.fill: textItem

    property color color: "#03A9F4"
    property color backgroundColor: "#ffffff"

    property Item textItem: parent
    property Item cursorParent: Window.contentItem

    readonly property bool selected: textItem && textItem.selectionStart != textItem.selectionEnd
    property alias menuMore: menuRect.more

    property alias active: marea.visible
    property real topPadding: 20

    property variant menuMap: {
        if(selected)
            return [
                        {"name": qsTr("Copy"), "action": function() { textItem.copy(); hideMenu() }},
                        {"name": qsTr("Delete"), "action": function() { textItem.remove(textItem.selectionStart, textItem.selectionEnd); hideMenu() }},
                        {"name": "<font family=\"%1\">%2</font>".arg(Awesome.family).arg(Awesome.fa_ellipsis_v), "action": function() { menuMore = true }}
                    ]
        else
            return [
                        {"name": qsTr("Paste"), "action": function() { textItem.paste(); hideMenu() }},
                        {"name": qsTr("Select All"), "action": function() { textItem.selectAll(); menuRect.showCursor() }}
                    ]
    }
    property variant menuMoreMap: [
        {"name": qsTr("Cut"), "action": function() { textItem.cut(); hideMenu() }},
        {"name": (selected? qsTr("Paste") : qsTr("Copy")), "action": function() {
            if(selected)
                textItem.paste()
            else
                textItem.copy()
            hideMenu()
        }},
        {"name": qsTr("Select All"), "action": function() { textItem.selectAll(); menuRect.showCursor() }},
        {"name": "<font family=\"%1\">%2</font>".arg(Awesome.family).arg(Awesome.fa_angle_left), "action": function() { menuMore = false }}
    ]

    onCursorParentChanged: if(menuRect.visible) menuRect.showCursor()

    Connections {
        target: textItem
        onActiveFocusChanged: {
            if(!textItem.activeFocus) {
                hideMenu()
            }
            else
            if(active) {
            }
        }
    }

    AsemanObject {
        id: prv
        property Item cursor0
        property Item cursor1
        property bool forceHidden: true

        property string itemText: textItem? textItem.text : ""
        property string nonEmptyText

        onNonEmptyTextChanged: {
            forceHidden = true
        }
        onItemTextChanged: {
            if (itemText.length == 0)
                return

            nonEmptyText = itemText
        }
        onForceHiddenChanged: if(forceHidden) menuRect.visible = false

        function switchCursors() {
            var tmp = cursor0.propertyName
            cursor0.propertyName = cursor1.propertyName
            cursor1.propertyName = tmp
        }
    }

    PointMapListener { id: mapListener; source: tcarea; dest: cursorParent }

    Item {
        id: menuRect
        x: mapListener.result.x + extraX
        y: mapListener.result.y + extraY
        width: menuBack.width + 10*Devices.density
        height: menuBack.height + 10*Devices.density
        visible: false
        parent: cursorParent
        clip: true
        z: 1000002

        property real extraX
        property real extraY

        onVisibleChanged: {
            if(!visible) more = false
            if(visible)
                BackHandler.pushHandler(menuRect, function(){ menuRect.visible = false; textItem.deselect() } )
            else
                BackHandler.removeHandler(menuRect)
        }

        property alias more: moreHandler.active

        BackAction { id: moreHandler }

        DropShadow {
            anchors.fill: menuItem
            horizontalOffset: 0
            verticalOffset: 1*Devices.density
            radius: 8*Devices.density
            samples: 16
            color: "#80000000"
            source: menuItem
            cached: true
        }

        Item {
            id: menuItem
            anchors.fill: parent

            Rectangle {
                id: menuBack
                anchors.centerIn: parent
                width: menuRect.more? menuColumn.width : menuRow.width
                height: menuRect.more? menuColumn.height : menuRow.height
                color: tcarea.backgroundColor
                radius: 3*Devices.density

                Behavior on width {
                    NumberAnimation { easing.type: Easing.OutCubic; duration: 300 }
                }
                Behavior on height {
                    NumberAnimation { easing.type: Easing.OutCubic; duration: 300 }
                }

                NullMouseArea { anchors.fill: parent }
            }

            Column {
                id: menuColumn
                visible: menuRect.more
                x: 5*Devices.density
                y: x

                Repeater {
                    model: menuMoreMap
                    delegate: QtControls.Button {
                        text: data.name
                        flat: true
                        width: 128*Devices.density
                        focusPolicy: Qt.NoFocus
                        onClicked: data.action()

                        property variant data: menuMoreMap[index]
                        Component.onCompleted: {
                            if(text.indexOf(Awesome.family) != -1) {
                                font.pixelSize = 13*Devices.fontDensity
                            }
                        }
                    }
                }
            }

            Row {
                id: menuRow
                visible: !menuRect.more
                x: 5*Devices.density
                y: x

                Repeater {
                    model: menuMap
                    delegate: QtControls.Button {
                        text: data.name
                        flat: true
                        focusPolicy: Qt.NoFocus
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: data.action()

                        property variant data: menuMap[index]
                        Component.onCompleted: {
                            if(text.indexOf(Awesome.family) != -1) {
                                font.pixelSize = 13*Devices.fontDensity
                                width = height*0.75
                            }
                        }
                    }
                }
            }
        }

        function showCursor() {
            var cItem = cursorParent
            var minX = cItem.width
            var maxX = 0
            var minY = cItem.height
            var maxY = 0
            for(var i=textItem.selectionStart; i<=textItem.selectionEnd; i++) {
                var rect = textItem.positionToRectangle(i)
                if(rect.x < minX)
                    minX = rect.x
                if(rect.x + rect.width > maxX)
                    maxX = rect.x + rect.width
                if(rect.y < minY)
                    minY = rect.y
                if(rect.y + rect.height > maxY)
                    maxY = rect.y + rect.height
            }

            var pnt = tcarea.mapToItem(cItem, 0, 0)
            minX += pnt.x
            maxX += pnt.x
            minY += pnt.y
            maxY += pnt.y

            var mrX = (maxX+minX)/2 - menuRect.width/2
            if(mrX < 0)
                mrX = 0
            if(mrX + menuRect.width > cItem.width)
                mrX = cItem.width - menuRect.width

            var mrY = minY - menuRect.height + 5*Devices.density
            if(mrY < 0)
                mrY = maxY + 30*Devices.density
            if(mrY + menuRect.height > cItem.height)
                mrY = cItem.height/2 - height/2

            extraX = mrX - pnt.x
            extraY = mrY - pnt.y

            menuRect.visible = true
            menuRect.more = false
        }
    }

    MouseArea {
        id: marea
        anchors.fill: parent
        visible: Devices.isAndroid && AsemanApp.qpaNoTextHandles
        onPressAndHold: {
            textItem.focus = true
            textItem.forceActiveFocus()
            prv.forceHidden = false
            menuRect.visible = false
            textItem.cursorVisible = false
//            textItem.focus = false
            var pos = textItem.positionAt(mouseX, mouseY)
            textItem.cursorPosition = pos
            textItem.selectWord()
            menuRect.showCursor()
        }
        onClicked: {
            prv.forceHidden = false
            var pos = textItem.positionAt(mouseX, mouseY)
            if(textItem.selectionStart != textItem.selectionEnd &&
               textItem.selectionStart < pos &&
               textItem.selectionEnd > pos && !menuRect.visible) {
                menuRect.showCursor()
            } else {
                textItem.deselect()
                textItem.cursorPosition = pos
                textItem.cursorVisible = true
                textItem.focus = true
                textItem.forceActiveFocus()
                menuRect.visible = false
                Devices.showKeyboard()
            }
        }
    }

    Item {
        id: cursorsScene
        width: tcarea.width
        height: tcarea.height
        parent: cursorParent
        x: mapListener.result.x
        y: mapListener.result.y
        z: 1000001
        visible: textItem && textItem.visible && textItem.activeFocus
    }

    Component {
        id: cursorComponent
        Item {
            id: cursorHandle
            width: 24*Devices.density
            height: width
            x: customPoint.x? customPoint.x : pnt.x - width/2 + leftPadding
            y: customPoint.y? customPoint.y : pnt.y + topPadding
            visible: {
                if(prv.forceHidden)
                    return false
                if(textItem.text.length == 0)
                    return false
                if(textItem && textItem.selectionStart != textItem.selectionEnd)
                    return true
                if(propertyName == "selectionStart")
                    return true
                return false
            }

            property real topPadding: textItem.topPadding? textItem.topPadding : 0
            property real leftPadding: textItem.leftPadding? textItem.leftPadding : 0

            Behavior on x {
                NumberAnimation { easing.type: Easing.OutCubic; duration: customPoint.x? 0 : 300 }
            }
            Behavior on y {
                NumberAnimation { easing.type: Easing.OutCubic; duration: customPoint.y? 0 : 300 }
            }

            property string propertyName: "selectionStart"

            property point pnt: {
                if(!textItem)
                    return Qt.point(-1, -1)
                if(textItem.selectionStart == textItem.selectionEnd && propertyName == "selectionEnd")
                    return Qt.point(-1, -1)

                var point = textItem.positionToRectangle(textItem[propertyName])
                return Qt.point(point.x + point.width/2, point.y + point.height)
            }
            property point customPoint: Qt.point(0, 0)

            Item {
                  id: mycanvas
                  anchors.fill: parent
                  rotation: {
                      var reverse = (textItem && textItem.horizontalAlignment==TextEdit.AlignRight? -1 : 1)
                      if(textItem && textItem.selectionStart == textItem.selectionEnd)
                          return 0
                      else
                      if(propertyName == "selectionStart")
                          return 45*reverse
                      else
                          return -45*reverse
                  }
                  transformOrigin: Item.Top

                  Rectangle {
                      id: src
                      anchors.fill: parent
                      color: tcarea.color
                      visible: false
                  }

                  Image {
                      id: mask
                      anchors.fill: parent
                      source: "files/text_select_handle_middle.png"
                      visible: false
                  }

                  OpacityMask {
                      anchors.fill: parent
                      source: src
                      maskSource: mask
                      cached: true
                  }

                  Behavior on rotation {
                      NumberAnimation { easing.type: Easing.OutCubic; duration: 300 }
                  }
              }

            MouseArea {
                anchors.fill: parent
                anchors.leftMargin: -10*Devices.density
                anchors.rightMargin: -10*Devices.density
                anchors.bottomMargin: -30*Devices.density
                onPositionChanged: {
                    var deltaX = mouseX-pinX
                    var deltaY = mouseY-pinY

                    customPoint.x = cursorHandle.x + deltaX
                    customPoint.y = cursorHandle.y + deltaY

                    var pos = textItem.positionAt(cursorHandle.x + cursorHandle.width/2, cursorHandle.y)
                    if(textItem.selectionStart == textItem.selectionEnd && propertyName == "selectionStart") {
                        textItem.cursorPosition = pos
                    } else if(propertyName == "selectionStart") {
                        if(pos < textItem.selectionEnd)
                            textItem.select(pos, textItem.selectionEnd)
                        else {
                            prv.switchCursors()
                            var rcvr = textItem.selectionEnd
                            if(rcvr == pos)
                                pos++
                            textItem.select(rcvr, pos)
                        }
                    } else {
                        if(pos > textItem.selectionStart)
                            textItem.select(textItem.selectionStart, pos)
                        else {
                            prv.switchCursors()
                            var rcvr = textItem.selectionStart
                            if(rcvr == pos)
                                pos--
                            textItem.select(pos, rcvr)
                        }
                    }
                }
                onPressed: {
                    pinPos = textItem[propertyName]
                    menuRect.visible = false
                    pinX = width/2
                    pinY = height
                }
                onReleased: {
                    customPoint = Qt.point(0, 0)
                    menuRect.showCursor()
                }

                property real pinX
                property real pinY
                property int pinPos
            }
        }
    }

    function hideMenu() {
        menuRect.visible = false
    }

    function close() {
        hideMenu()
        prv.forceHidden = true
    }

    Component.onCompleted: {
        prv.cursor0 = cursorComponent.createObject(cursorsScene, {"propertyName": "selectionStart"})
        prv.cursor1 = cursorComponent.createObject(cursorsScene, {"propertyName": "selectionEnd"})
    }
}
