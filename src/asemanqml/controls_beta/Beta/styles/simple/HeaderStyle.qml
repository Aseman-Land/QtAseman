import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Controls.Beta 3.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitHeight: Devices.standardTitleBarHeight + Devices.statusBarHeight

    padding {
        top: Devices.statusBarHeight
    }

    Rectangle {
        anchors.fill: parent
        anchors.topMargin: Devices.statusBarHeight
        color: control.Style.primaryColor

        Root.Label {
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 10 * Devices.fontDensity
            text: control.title
            color: control.Style.primaryTextColor
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: control.Style.foregroundColor
        height: 1
        opacity: 0.1
    }
}
