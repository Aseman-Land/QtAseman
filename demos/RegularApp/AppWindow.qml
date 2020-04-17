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

import QtQuick 2.7
import QtQuick.Window 2.2
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import AsemanQml.Viewport 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Dialogs 1.2
import "graphical"
import "nongraphical"
import "static"
import "models"
import "global"

AsemanWindow {
    id: mainWin
    width: 480
    height: 720
    title: qsTr("Hello World")
    visible: true
    backController: true

    Material.accent: Material.LightBlue
    Material.theme: Material.Light

    property bool mirror

    LayoutMirroring.enabled: mirror
    LayoutMirroring.childrenInherit: true

    Rectangle {
        anchors.fill: parent
        color: "#000000"
    }

    Viewport {
        id: viewport
        anchors.fill: parent

        mainItem: Rectangle {
            anchors.fill: parent

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
                        text: "Right To Left"
                        onClicked: layoutSwitch.checked = !layoutSwitch.checked
                        Switch {
                            id: layoutSwitch
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            onCheckedChanged: mirror = checked
                        }
                    }
                    MainMenuItem {
                        text: "Graphical Components"
                        onClicked: viewport.append(graphicalComponents, {}, "stack")
                    }
                    MainMenuItem {
                        text: "Model Components"
                        onClicked: viewport.append(modelComponents, {}, "ios-bottomdrawer")
                    }
                    MainMenuItem {
                        text: "Non-Graphical Components"
                        onClicked: viewport.append(nonGraphicalComponents, {}, "popup")
                    }
                    MainMenuItem {
                        text: "Static Components"
                        onClicked: viewport.append(staticComponents, {}, "activity")
                    }
                }
            }

            RoundButton {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 10 * Devices.density
                highlighted: true
                text: qsTr("Github")
                onClicked: Qt.openUrlExternally("https://github.com/Aseman-Land/aseman-qt-tools")
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
                color: "#18f"
                text: qsTr("SlidePageManager")
                shadow: true
            }
        }
    }

    Component {
        id: staticComponents
        StaticComponentsExample {
            anchors.fill: parent
            onAppendRequest: viewport.append(component, {}, "stack")
        }
    }

    Component {
        id: graphicalComponents
        GraphicalComponentsExample {
            anchors.fill: parent
            onAppendRequest: viewport.append(component, {}, "popup")
        }
    }

    Component {
        id: modelComponents
        ModelComponentExamples {
            width: Viewport.viewport.width
            height: Viewport.viewport.height * 0.6
            onAppendRequest: viewport.append(component, {}, "popup")
        }
    }

    Component {
        id: nonGraphicalComponents
        NonGraphicalComponentsExample {
            anchors.fill: parent
            onAppendRequest: viewport.append(component, {}, "activity")
        }
    }
}
