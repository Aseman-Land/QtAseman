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
import AsemanQml.Models 2.0

AsemanGridView {
    id: grid
    model: fsmodel
    clip: true

    property alias root: fsmodel.folder
    property alias filters: fsmodel.nameFilters
    property alias showDotAndDotDot: fsmodel.showDotAndDotDot
    property color itemsLabelColor: "#333333"
    
    signal clickedOnFile(variant fileUrl)

    FileSystemModel {
        id: fsmodel
    }

    SystemPalette {
        id: palette
    }

    ListObject {
        id: paths_list
    }

    onRootChanged: {
        if(paths_list.last() != root)
            paths_list.append(root)
    }

    property real gridWidth: 92*Devices.density

    cellWidth: width/Math.floor(width/gridWidth)
    cellHeight: gridWidth

    delegate: Item {
        width: grid.cellWidth
        height: grid.cellHeight

        Rectangle {
            anchors.fill: parent
            anchors.margins: 1*Devices.density
            radius: 3*Devices.density
            color: palette.highlight
            opacity: marea.pressed? 0.2 : 0
        }

        Column {
            height: parent.height - 10*Devices.density
            anchors.centerIn: parent
            spacing: 4*Devices.density

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                width: height
                height: parent.height - txt.height - 10*Devices.density
                asynchronous: true
                sourceSize: Qt.size(width*2, height*2)
                fillMode: Image.PreserveAspectCrop
                clip: true
                source: {
                    if(model.fileIsDir)
                        return "files/folder.png"
                    else
                    if(model.fileMime.indexOf("image") >= 0)
                        return model.fileUrl
                    else
                        return "files/unknown.png"
                }
            }

            Text {
                id: txt
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                text: model.fileName
                color: itemsLabelColor
                wrapMode: Text.WrapAnywhere
                elide: Text.ElideRight
                maximumLineCount: 1
                font.pixelSize: 9*Devices.fontDensity
                horizontalAlignment: Text.AlignHCenter
            }
        }

        MouseArea {
            id: marea
            anchors.fill: parent
            onClicked: {
                if(model.fileIsDir)
                    fsmodel.folder = model.filePath
                else
                    clickedOnFile(model.fileUrl)
            }
        }
    }

    function back() {
        paths_list.takeLast()
        if(paths_list.count != 0)
            root = paths_list.last()

        if(paths_list.count <= 0)
            return false
        else
            return true
    }
}
