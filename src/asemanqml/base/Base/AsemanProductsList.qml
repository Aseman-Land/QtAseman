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
import QtQuick.XmlListModel 2.0

Rectangle {
    width: 100
    height: 62

    property alias source: xmlModel.source

    XmlListModel {
        id: xmlModel
        query: "/products/item"

        XmlRole { name: "name"; query: "info/@name/string()" }
        XmlRole { name: "version"; query: "info/@version/string()" }
        XmlRole { name: "publisher"; query: "info/@publisher/string()" }
        XmlRole { name: "type"; query: "info/@type/string()" }
        XmlRole { name: "description"; query: "description/string()" }
        XmlRole { name: "icon"; query: "icon/@src/string()" }
        XmlRole { name: "link"; query: "link/@dst/string()" }
    }

    AsemanListView {
        id: listv
        anchors.fill: parent
        model: xmlModel
        delegate: Item {
            width: listv.width
            height: row.height + 16*Devices.density

            Row {
                id: row
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 10*Devices.density
                spacing: 8*Devices.density

                Image {
                    id: img
                    y: 8*Devices.density
                    height: 48*Devices.density
                    width: height
                    sourceSize: Qt.size(width*2, height*2)
                    source: model.icon==""? "" : Tools.fileParent(xmlModel.source) + "/" + model.icon
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 4*Devices.density

                    Row {
                        spacing: 4*Devices.density

                        Text {
                            font.pixelSize: 11*Devices.fontDensity
                            color: "#333333"
                            text: model.name
                        }

                        Text {
                            font.pixelSize: 9*Devices.fontDensity
                            anchors.bottom: parent.bottom
                            color: "#0d80ec"
                            text: "by " + model.publisher
                        }
                    }

                    Text {
                        width: row.width - img.width - row.spacing*2 - btn.width
                        font.pixelSize: 9*Devices.fontDensity
                        color: "#777777"
                        text: model.description
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        maximumLineCount: 3
                        elide: Text.ElideRight
                    }
                }

                Button {
                    id: btn
                    anchors.verticalCenter: parent.verticalCenter
                    border.width: 1*Devices.density
                    border.color: highlightColor
                    textColor: press? "#ffffff" : highlightColor
                    width: 64*Devices.density
                    radius: 3*Devices.density
                    text: "Home"
                    onClicked: Qt.openUrlExternally(model.link)
                }
            }
        }
    }

    Indicator {
        anchors.centerIn: parent
        indicatorSize: 22*Devices.density
        light: false
        modern: true
        running: xmlModel.status == XmlListModel.Loading
    }

    ScrollBar {
        scrollArea: listv; height: listv.height
        width: 6*Devices.density
        anchors.right: listv.right; anchors.top: listv.top;
        color: "#0d80ec"
    }
}
