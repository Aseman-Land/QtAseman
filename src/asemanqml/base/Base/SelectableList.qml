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
import AsemanQml.GraphicalEffects 2.0
import AsemanQml.Base 2.0

Item {
    id: seletable_list
    width: 100
    height: 62
    clip: true

    property color color: "transparent"
    property alias currentIndex: list.currentIndex
    property variant items: new Array
    property color textsColor
    property color splitersColor: "#66bbbbbb"
    property real itemsHeight: 40*Devices.density

    property variant nameMethodObject: seletable_list
    property string nameMethodFunction: "itemName"

    property bool debugMode: false

    onItemsChanged: {
        list.refresh()
    }

    Item {
        id: background
        width: parent.width
        height: parent.height*2
        anchors.centerIn: parent
        opacity: 0

        AsemanListView {
            id: list
            anchors.fill: parent
            clip: true
            preferredHighlightBegin: height/2 - itemsHeight/2
            preferredHighlightEnd: height/2 + itemsHeight/2
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveDuration: 300
            highlightMoveVelocity: -1
            snapMode: ListView.SnapToItem
            model: listModel

            ListModel { id: listModel }

            delegate: Item {
                width: list.width
                height: itemsHeight

                Text {
                    id: txt
                    anchors.centerIn: parent
                    font.family: AsemanApp.globalFont.family
                    font.pixelSize: Math.floor(11*Devices.fontDensity)
                    text: Tools.call(nameMethodObject,nameMethodFunction,Qt.DirectConnection,model.name)
                    color: textsColor
                }
            }

            function refresh() {
                if(debugMode)
                    console.debug(items.length)
                for(var i=0; i<items.length; i++) {
                    if(listModel.count <= i)
                        listModel.append({"name": items[i]})
                    else
                        listModel.setProperty(i, "name", items[i])
                }
                if(items.length < listModel.count)
                    listModel.remove(items.length, listModel.count - items.length)
            }
        }
    }

    Item {
        id: scene
        anchors.fill: parent
        visible: false

        Item {
            id: top_part
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: parent.height/2 - 1.3*itemsHeight/2
            clip: true

            Desaturate {
                source: background
                width: background.width
                height: background.height
                y: -0.25*height
                transformOrigin: Item.Center
                scale: 0.8
                opacity: 0.7
            }
        }

        Rectangle {
            id: center_part
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: top_part.bottom
            anchors.bottom: bottom_part.top
            clip: true
            color: seletable_list.color

            Desaturate {
                source: background
                width: background.width
                height: background.height
                anchors.centerIn: parent
                transformOrigin: Item.Center
            }
        }

        Item {
            id: bottom_part
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: parent.height/2 - 1.3*itemsHeight/2
            clip: true

            Desaturate {
                source: background
                width: background.width
                height: background.height
                y: parent.height - 0.75*height
                transformOrigin: Item.Center
                scale: 0.8
                opacity: 0.7
            }
        }

        Rectangle {
            height: 1*Devices.density
            width: parent.width
            anchors.top: top_part.bottom
            color: splitersColor
        }

        Rectangle {
            height: 1*Devices.density
            width: parent.width
            anchors.bottom: bottom_part.top
            color: splitersColor
        }
    }

    Rectangle {
        id: mask
        anchors.fill: parent
        visible: false
        gradient: Gradient{
            GradientStop { position: 0.00; color: "#00000000" }
            GradientStop { position: 0.22; color: "#fff" }
            GradientStop { position: 0.77; color: "#fff" }
            GradientStop { position: 1.00; color: "#00000000" }
        }
    }

    OpacityMask {
        maskSource: mask
        source: scene
        anchors.fill: parent
    }

    function positionViewAtIndex( index, force ) {
        currentIndex = index
        if(force)
            list.positionViewAtIndex(index, ListView.Center)
    }

    function itemName( index ) {
        return index
    }
}
