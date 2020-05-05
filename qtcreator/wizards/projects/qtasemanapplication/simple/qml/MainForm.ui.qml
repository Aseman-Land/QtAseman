import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import AsemanQml.Viewport 2.0

Page {

    property alias menuButton: menuButton
    property alias drawer: drawer
    property alias btn: btn
    property alias menuBtn: menuBtn

    Column {
        anchors.centerIn: parent

        Button {
            id: menuBtn
            font.pixelSize: 12 * Devices.fontDensity
            text: qsTr("Menu") + Translations.refresher
        }

        Button {
            id: btn
            font.pixelSize: 12 * Devices.fontDensity
            text: qsTr("Popup") + Translations.refresher
        }
    }

    Header {
        id: header
        anchors.left: parent.left
        anchors.right: parent.right
        color: Material.primary
        text: qsTr("App") + Translations.refresher
    }

    Drawer {
        id: drawer
        anchors.fill: parent
        delegate: Rectangle {
            anchors.fill: parent
        }
    }

    HeaderMenuButton {
        id: menuButton
        ratio: drawer.percent
        buttonColor: ratio > 0.1? "black" : "white"
    }
}
