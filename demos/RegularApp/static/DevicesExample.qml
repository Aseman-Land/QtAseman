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
                title: qsTr("Device Properties")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: Math.floor(width/(180*Devices.density))

                    Label { text: "isMobile: " + (Devices.isMobile? "<b>true</b>" : "false") }
                    Label { text: "isTablet: " + (Devices.isTablet? "<b>true</b>" : "false") }
                    Label { text: "isLargeTablet: " + (Devices.isLargeTablet? "<b>true</b>" : "false") }
                    Label { text: "isTouchDevice: " + (Devices.isTouchDevice? "<b>true</b>" : "false") }
                    Label { text: "isDesktop: " + (Devices.isDesktop? "<b>true</b>" : "false") }
                    Label { text: "isMacX: " + (Devices.isMacX? "<b>true</b>" : "false") }
                    Label { text: "isWindows: " + (Devices.isWindows? "<b>true</b>" : "false") }
                    Label { text: "isWindows8: " + (Devices.isWindows8? "<b>true</b>" : "false") }
                    Label { text: "isLinux: " + (Devices.isLinux? "<b>true</b>" : "false") }
                    Label { text: "isAndroid: " + (Devices.isAndroid? "<b>true</b>" : "false") }
                    Label { text: "isIOS: " + (Devices.isIOS? "<b>true</b>" : "false") }
                    Label { text: "isUbuntuTouch: " + (Devices.isUbuntuTouch? "<b>true</b>" : "false") }
                    Label { text: "isWindowsPhone: " + (Devices.isWindowsPhone? "<b>true</b>" : "false") }
                }
            }

            GroupBox {
                title: qsTr("Screen Properties")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: Math.floor(width/(180*Devices.density))

                    Label { text: "lcdPhysicalSize: <b>" + Math.floor(Devices.lcdPhysicalSize*10)/10 + "</b>" }
                    Label { text: "lcdPhysicalWidth: <b>" + Math.floor(Devices.lcdPhysicalWidth*10)/10 + "</b>" }
                    Label { text: "lcdPhysicalHeight: <b>" + Math.floor(Devices.lcdPhysicalHeight*10)/10 + "</b>" }
                    Label { text: "lcdDpiX: <b>" + Math.floor(Devices.lcdDpiX*10)/10 + "</b>" }
                    Label { text: "lcdDpiY: <b>" + Math.floor(Devices.lcdDpiY*10)/10 + "</b>" }
                    Label { text: "screenSize: <b>" + Devices.screenSize.width + "x" + Devices.screenSize.height + "</b>" }
                    Label { text: "keyboardHeight: <b>" + Devices.keyboardHeight + "</b>" }
                }
            }

            GroupBox {
                title: qsTr("Densities")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: Math.floor(width/(180*Devices.density))

                    Label { text: "density: <b>" + Math.floor(Devices.density*10)/10 + "</b>" }
                    Label { text: "densityDpi: <b>" + Math.floor(Devices.densityDpi*10)/10 + "</b>" }
                    Label { text: "fontDensity: <b>" + Math.floor(Devices.fontDensity*10)/10 + "</b>" }
                }
            }

            GroupBox {
                title: qsTr("Operating System")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: Math.floor(width/(180*Devices.density))

                    Label { text: "transparentStatusBar: <b>" + Devices.transparentStatusBar + "</b>" }
                    Label { text: "transparentNavigationBar: <b>" + Devices.transparentNavigationBar + "</b>" }
                    Label { text: "standardTitleBarHeight: <b>" + Math.floor(Devices.standardTitleBarHeight*10)/10 + "</b>" }
                    Label { text: "statusBarHeight: <b>" + Math.floor(Devices.statusBarHeight*10)/10 + "</b>" }
                    Label { text: "navigationBarHeight: <b>" + Math.floor(Devices.navigationBarHeight*10)/10 + "</b>" }

                    Label { text: "clipboard: <b>" + Devices.clipboard + "</b>" }
                    Label { text: "keyboard: <b>" + Devices.keyboard + "</b>" }

                    Label { text: "deviceName: <b>" + Devices.deviceName + "</b>" }
                    Label { text: "localFilesPrePath: <b>" + Devices.localFilesPrePath + "</b>" }
                }
            }

            GroupBox {
                title: qsTr("Paths")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: 1

                    Label { text: "cameraLocation: <b>" + Devices.cameraLocation + "</b>" }
                    Label { text: "picturesLocation: <b>" + Devices.picturesLocation + "</b>" }
                    Label { text: "musicsLocation: <b>" + Devices.musicsLocation + "</b>" }
                    Label { text: "documentsLocation: <b>" + Devices.documentsLocation + "</b>" }
                    Label { text: "downloadsLocation: <b>" + Devices.downloadsLocation + "</b>" }
                    Label { text: "resourcePath: <b>" + Devices.resourcePathQml + "</b>" }
                    Label { text: "libsPath: <b>" + Devices.libsPath + "</b>" }
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
                        Button { text: "showKeyboard"; onClicked: Devices.showKeyboard() }
                        Button { text: "hideKeyboard"; onClicked: Devices.hideKeyboard() }
                    }
                    RowLayout {
                        Button { text: "Share"; onClicked: Devices.share("AsemanQtTools", "It's a message from AsemanQtTools") }
                        Button { text: "Open File"; onClicked: Devices.openFile("/path/to/file") }
                    }
                    RowLayout {
                        Button { text: "Share File"; onClicked: Devices.shareFile("/path/to/file") }
                        Button { text: "Camera"; onClicked: Devices.startCameraPicture() }
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
        text: qsTr("Devices")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }
}
