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
import AsemanTools 1.0
import "../global"

Rectangle {
    id: scItem
    color: masterPalette.window

    signal appendRequest(variant component)

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
                text: "AsemanApp"
                onClicked: appendRequest(asemanApp_component)
            }
            MainMenuItem {
                text: "BackHandler"
                onClicked: appendRequest(backHandler_component)
            }
            MainMenuItem {
                text: "Devices"
                onClicked: appendRequest(devices_component)
            }
            MainMenuItem {
                text: "Desktop"
                onClicked: appendRequest(desktop_component)
            }
            MainMenuItem {
                text: "TextTools"
                onClicked: appendRequest(textToolsComponent)
            }
            MainMenuItem {
                text: "Tools"
                onClicked: appendRequest(toolsComponent)
            }
            MainMenuItem {
                text: "View"
                onClicked: appendRequest(view_component)
            }
        }
    }

    PhysicalScrollBar {
        anchors.right: flick.right
        anchors.top: flick.top
        height: flick.height
        width: 6*Devices.density
        color: masterPalette.highlight
        scrollArea: flick
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("Static Components")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }

    Component {
        id: asemanApp_component
        AsemanAppExample {
            anchors.fill: parent
        }
    }

    Component {
        id: backHandler_component
        BackHandlerExample {
            anchors.fill: parent
        }
    }

    Component {
        id: devices_component
        DevicesExample {
            anchors.fill: parent
        }
    }

    Component {
        id: desktop_component
        DesktopExample {
            anchors.fill: parent
        }
    }

    Component {
        id: textToolsComponent
        TextToolsExample {
            anchors.fill: parent
        }
    }

    Component {
        id: toolsComponent
        ToolsExample {
            anchors.fill: parent
        }
    }

    Component {
        id: view_component
        ViewExample {
            anchors.fill: parent
        }
    }
}
