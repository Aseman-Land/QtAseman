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
    id: share_dialog
    anchors.fill: parent

    property bool started: false
    property variant sources

    onSourcesChanged: apps_list.refresh()

    MimeApps {
        id: mime_apps
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton | Qt.LeftButton
        hoverEnabled: true
        onWheel: wheel.accepted = true
        onClicked: hideSubMessage()
    }

    Header {
        id: header
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        z: 10
    }

    Text {
        id: title
        x: 40*Devices.density
        y: 60*Devices.density
        text: qsTr("Select Application")
        font.pixelSize: Math.floor(25*Devices.fontDensity)
        font.weight: Font.Light
        font.family: AsemanApp.globalFont.family
        color: "#333333"
    }

    AsemanListView {
        id: apps_list
        anchors.left: title.left
        anchors.right: parent.right
        anchors.top: title.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20*Devices.density
        anchors.topMargin: 10*Devices.density
        model: ListModel{}
        clip: true
        delegate: Rectangle {
            id: item
            height: 48*Devices.density
            width: apps_list.width
            color: marea.pressed? "#880d80ec" : "#00000000"

            Image {
                id: img
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 4*Devices.density
                height: 36*Devices.density
                width: height
                sourceSize: Qt.size(width,height)
                source: "image://icon/" + mime_apps.appIcon(appId)
            }

            Text {
                id: txt
                anchors.left: img.right
                anchors.leftMargin: 10*Devices.density
                anchors.verticalCenter: parent.verticalCenter
                font.family: AsemanApp.globalFont.family
                font.pixelSize: Math.floor(9*Devices.fontDensity)
                text: mime_apps.appName(appId)
            }

            MouseArea {
                id: marea
                anchors.fill: parent
                onClicked: {
                    mime_apps.openFiles(appId,share_dialog.sources)
                    hideSubMessage()
                }
            }
        }

        function refresh() {
            model.clear()
            if( !share_dialog.sources || share_dialog.sources.length == 0 )
                return

            var apps = mime_apps.appsOfFile(share_dialog.sources[0])
            for( var i=0; i<apps.length; i++ )
                model.append({"appId":apps[i]})
        }

        Component.onCompleted: refresh()
    }

    ScrollBar {
        scrollArea: apps_list; height: apps_list.height; width: 6*Devices.density
        anchors.right: apps_list.right; anchors.top: apps_list.top; color: "#333333"
    }

    function hide() {
        started = false
    }

    Component.onCompleted: started = true
}
