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
import AsemanQml.Controls 2.0
import AsemanQml.Models 2.0
import "../global"

Item {
    id: scItem

    signal appendRequest(variant component)

    Rectangle {
        anchors.fill: parent
        color: masterPalette.window
        opacity: 0.5
    }

    AsemanFlickable {
        id: flick
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        contentWidth: column.width
        contentHeight: column.height

        Column {
            id: column
            width: flick.width

            MainMenuItem {
                text: "CountriesModel"
                onClicked: appendRequest(countriesModel_component)
            }

            MainMenuItem {
                text: "FileSystemModel"
                onClicked: appendRequest(fileSystemModel_component)
            }
        }
    }

    HScrollBar {
        anchors.right: flick.right
        anchors.top: flick.top
        height: flick.height
        width: 6*Devices.density
        color: "#18f"
        scrollArea: flick
    }

    Header {
        id: header
        width: parent.width
        color: "transparent"
        text: qsTr("Model Components")
        shadow: true
        light: false
        shadowOpacity: 0
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }

    Component {
        id: countriesModel_component
        CountriesModelExample {
            anchors.fill: parent
        }
    }

    Component {
        id: fileSystemModel_component
        FileSystemModelExample {
            anchors.fill: parent
        }
    }
}
