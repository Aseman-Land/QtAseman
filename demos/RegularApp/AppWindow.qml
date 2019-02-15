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
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
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
    height: 640
    title: qsTr("Hello World")
    visible: true
    backController: true

    Material.accent: Material.LightBlue
    Material.theme: Material.Light

    Rectangle {
        anchors.fill: parent
        color: "#000000"
    }

    SlidePageManager {
        id: pageManger
        anchors.fill: parent
        direction: (mainItem && mainItem.pageManagerDirection? Qt.Vertical : Qt.Horizontal)

        LayoutMirroring.enabled: View.layoutDirection == Qt.RightToLeft
        LayoutMirroring.childrenInherit: true

        mainComponent: Rectangle {
            anchors.fill: parent

            property alias pageManagerDirection: pManagerSwitch.checked

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
                        text: "Vertical page manager"
                        onClicked: pManagerSwitch.checked = !pManagerSwitch.checked
                        Switch {
                            id: pManagerSwitch
                            anchors.verticalCenter: parent.verticalCenter
                            x: View.layoutDirection==Qt.LeftToRight? parent.width - width : 0
                        }
                    }
                    MainMenuItem {
                        text: "Right To Left"
                        onClicked: layoutSwitch.checked = !layoutSwitch.checked
                        Switch {
                            id: layoutSwitch
                            anchors.verticalCenter: parent.verticalCenter
                            x: View.layoutDirection==Qt.LeftToRight? parent.width - width : 0
                            onCheckedChanged: View.layoutDirection = (checked? Qt.RightToLeft : Qt.LeftToRight)
                        }
                    }
                    MainMenuItem {
                        text: "Graphical Components"
                        onClicked: pageManger.append(graphicalComponents)
                    }
                    MainMenuItem {
                        text: "Model Components"
                        onClicked: pageManger.append(modelComponents)
                    }
                    MainMenuItem {
                        text: "Non-Graphical Components"
                        onClicked: pageManger.append(nonGraphicalComponents)
                    }
                    MainMenuItem {
                        text: "Static Components"
                        onClicked: pageManger.append(staticComponents)
                    }
                    MainMenuItem {
                        text: "AsemanQtTools Github"
                        onClicked: Qt.openUrlExternally("https://github.com/Aseman-Land/aseman-qt-tools")
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
                text: qsTr("SlidePageManager")
                shadow: true
            }
        }
    }

    Component {
        id: staticComponents
        StaticComponentsExample {
            anchors.fill: parent
            onAppendRequest: pageManger.append(component)
        }
    }

    Component {
        id: graphicalComponents
        GraphicalComponentsExample {
            anchors.fill: parent
            onAppendRequest: pageManger.append(component)
        }
    }

    Component {
        id: modelComponents
        ModelComponentExamples {
            anchors.fill: parent
            onAppendRequest: pageManger.append(component)
        }
    }

    Component {
        id: nonGraphicalComponents
        NonGraphicalComponentsExample {
            anchors.fill: parent
            onAppendRequest: pageManger.append(component)
        }
    }
}
