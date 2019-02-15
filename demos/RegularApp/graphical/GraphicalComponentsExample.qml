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
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import "../global"

Rectangle {
    id: gcItem
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
                text: "Side Menu"
                onClicked: appendRequest(sideMenu_component)
            }
            MainMenuItem {
                text: "Menu Controller"
                onClicked: appendRequest(menuController_component)
            }
            MainMenuItem {
                text: "Material Button"
                onClicked: appendRequest(materialButton_component)
            }
            MainMenuItem {
                text: "Show Panel"
                onClicked: btmPanel.item = qmlcontrols_component.createObject(btmPanel)
            }
            MainMenuItem {
                text: "Show Popup"
                onClicked: msgDialog.visible = true
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
        text: qsTr("Graphical Components")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }

    BottomPanel {
        id: btmPanel
    }

    Popup {
        id: msgDialog
        x: (gcItem.width - width) / 2
        y: (gcItem.height - height) / 2
        width: Math.min(gcItem.width, gcItem.height) / 3 * 2
        height: settingsColumn.implicitHeight + topPadding + bottomPadding
        modal: true
        focus: true

        contentItem: ColumnLayout {
            id: settingsColumn
            spacing: 20
            z: 100

            Label {
                text: "Message"
                font.bold: true
            }

            Label {
                text: "It's just a test message :)"
            }

            RowLayout {
                spacing: 10

                Button {
                    id: okButton
                    text: "Ok"
                    onClicked: msgDialog.close()

                    Material.foreground: Material.LightBlue
                    Material.background: "transparent"
                    Material.elevation: 0

                    Layout.preferredWidth: 0
                    Layout.fillWidth: true
                }
            }
        }
    }

    Component {
        id: menuController_component
        MenuControllerExample {
            anchors.fill: parent
        }
    }

    Component {
        id: sideMenu_component
        SideMenuExample {
            anchors.fill: parent
        }
    }

    Component {
        id: materialButton_component
        MaterialButtonExample {
            anchors.fill: parent
        }
    }

    Component {
        id: qmlcontrols_component
        Rectangle {
            height: gcItem.height/2
            width: gcItem.width
            NullMouseArea { anchors.fill: parent }
            QmlControls { anchors.fill: parent }
        }
    }
}
