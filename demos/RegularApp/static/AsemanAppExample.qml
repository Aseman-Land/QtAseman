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

Rectangle {
    color: masterPalette.window
    clip: true

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
            spacing: 20*Devices.density

            Item { height: 20*Devices.density; width: 10 }
            GroupBox {
                title: qsTr("Paths")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: Math.floor(width/(180*Devices.density))

                    Label { text: "homePath: <b>" + AsemanApp.homePath + "</b>" }
                    Label { text: "startPath: <b>" + AsemanApp.startPath + "</b>" }
                    Label { text: "appPath: <b>" + AsemanApp.appPath + "</b>" }
                    Label { text: "appFilePath: <b>" + AsemanApp.appFilePath + "</b>" }
                    Label { text: "logPath: <b>" + AsemanApp.logPath + "</b>" }
                    Label { text: "confsPath: <b>" + AsemanApp.confsPath + "</b>" }
                    Label { text: "tempPath: <b>" + AsemanApp.tempPath + "</b>" }
                    Label { text: "backupsPath: <b>" + AsemanApp.backupsPath + "</b>" }
                    Label { text: "cameraPath: <b>" + AsemanApp.cameraPath + "</b>" }
                }
            }

            GroupBox {
                title: qsTr("Statuses")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: Math.floor(width/(180*Devices.density))

                    Label { text: "isDebug: " + (AsemanApp.isDebug? "<b>true</b>" : "false") }
                    Label {
                        text: "appType: <b>" + appTypeName + "</b>"
                        property string appTypeName: {
                            switch(AsemanApp.appType) {
                            case AsemanApp.NoneApplication:
                                return "NoneApplication"
                            case AsemanApp.CoreApplication:
                                return "CoreApplication"
                            case AsemanApp.GuiApplication:
                                return "GuiApplication"
                            case AsemanApp.WidgetApplication:
                                return "WidgetApplication"
                            }
                        }
                    }
                    Label { text: "isRunning: " + (AsemanApp.isRunning? "<b>true</b>" : "false") }
                    Label {
                        text: "applicationState: <b>" + applicationStateName + "</b>"
                        property string applicationStateName: {
                            switch(AsemanApp.applicationState) {
                            case AsemanApp.ApplicationSuspended:
                                return "Suspended"
                            case AsemanApp.ApplicationHidden:
                                return "Hidden"
                            case AsemanApp.ApplicationInactive:
                                return "Inactive"
                            case AsemanApp.ApplicationActive:
                                return "Active"
                            }
                        }
                    }
                    Label { text: "quitOnLastWindowClosed: " + (AsemanApp.quitOnLastWindowClosed? "<b>true</b>" : "false") }
                }
            }

            GroupBox {
                title: qsTr("App Details")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: 1

                    Label { text: "applicationName: <b>" + AsemanApp.applicationName + "</b>" }
                    Label { text: "applicationVersion: <b>" + AsemanApp.applicationVersion + "</b>" }
                    Label { text: "organizationName: <b>" + AsemanApp.organizationName + "</b>" }
                    Label { text: "organizationDomain: <b>" + AsemanApp.organizationDomain + "</b>" }
                    Label { text: "applicationAbout: <b>" + AsemanApp.applicationAbout + "</b>" }
                    Label { text: "applicationId: <b>" + AsemanApp.applicationId + "</b>" }
                    Label { text: "applicationDisplayName: <b>" + AsemanApp.applicationDisplayName + "</b>" }
                }
            }

            GroupBox {
                title: qsTr("Methods")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: 1

                    RowLayout {
                        Button { text: "back"; onClicked: AsemanApp.back() }
                    }
                }
            }
            Item { height: 20*Devices.density; width: 10 }
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
        text: qsTr("AsemanApp")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }
}
