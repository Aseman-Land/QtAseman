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
    id: about
    clip: true

    property variant list: new Array
    property color defaultColor: "#333333"
    property color framesColor: main_listv.currentIndex<0? defaultColor : list[main_listv.currentIndex].color
    property color textsColor: {
        var mid = (framesColor.r + framesColor.g + framesColor.b)/3
        if(mid > 0.7)
            return "#333333"
        else
            return "#ffffff"
    }

    AsemanListView {
        id: main_listv
        anchors.top: header.bottom
        anchors.bottom: footer.top
        width: parent.width
        model: about.list
        orientation: Qt.Horizontal
        highlightMoveDuration: 300
        highlightMoveVelocity: -1
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightFollowsCurrentItem: true
        snapMode: ListView.SnapOneItem
        delegate: Item {
            id: item
            width: main_listv.width
            height: main_listv.height
            property variant object
            Component.onCompleted: {
                object = list[index].delegate.createObject(item)
                object.anchors.fill = item
            }
        }
    }

    Rectangle {
        id: header
        width: parent.width
        height: Devices.standardTitleBarHeight + View.statusBarHeight
        color: framesColor

        Behavior on color {
            ColorAnimation {easing.type: Easing.OutCubic; duration: 300}
        }

        Text {
            id: title_txt
            width: parent.width - height - 6*Devices.density
            height: Devices.standardTitleBarHeight
            y: View.statusBarHeight
            x: View.layoutDirection==Qt.RightToLeft? 0 : parent.width-width
            verticalAlignment: Text.AlignVCenter
            color: textsColor
            font.family: AsemanApp.globalFont.family
            font.pixelSize: 14*Devices.fontDensity
            text: main_listv.currentIndex<0? "" : list[main_listv.currentIndex].title
        }

        Rectangle {
            height: 4*Devices.density
            width: parent.width
            anchors.top: parent.bottom
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#33000000" }
                GradientStop { position: 1.0; color: "#00000000" }
            }
        }
    }

    Rectangle {
        id: footer
        width: parent.width
        anchors.bottom: parent.bottom
        height: Devices.standardTitleBarHeight*1.2
        color: header.color

        Rectangle {
            height: 4*Devices.density
            width: parent.width
            anchors.bottom: parent.top
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#00000000" }
                GradientStop { position: 1.0; color: "#33000000" }
            }
        }

        AsemanListView {
            id: footer_listv
            anchors.fill: parent
            model: about.list
            highlightMoveDuration: main_listv.highlightMoveDuration
            highlightMoveVelocity: main_listv.highlightMoveVelocity
            orientation: Qt.Horizontal
            currentIndex: main_listv.currentIndex

            preferredHighlightBegin: width*0.2
            preferredHighlightEnd: width*0.8
            highlightRangeMode: ListView.ApplyRange

            property real itemsWidth: {
                var res = footer_listv.width/footer_listv.count
                if(res < 92*Devices.density)
                    res = 92*Devices.density
                return res
            }

            delegate: Rectangle {
                id: fitem
                height: footer_listv.height
                width: footer_listv.itemsWidth
                color: "#00000000"

                Column {
                    anchors.centerIn: parent
                    spacing: 2*Devices.density

                    Image {
                        height: fitem.height/2
                        width: height
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: list[index].icon
                        sourceSize: Qt.size(width*2, height*2)
                        fillMode: Image.PreserveAspectFit
                    }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: AsemanApp.globalFont.family
                        font.pixelSize: 8*Devices.fontDensity
                        color: textsColor
                        text: list[index].title
                    }
                }

                MouseArea {
                    id: marea
                    anchors.fill: parent
                    onClicked: main_listv.currentIndex = index
                }
            }

            highlight: Item {
                width: footer_listv.itemsWidth
                height: footer_listv.height

                Rectangle {
                    width: parent.width
                    height: 5*Devices.density
                    color: textsColor
                }
            }
        }
    }
}
