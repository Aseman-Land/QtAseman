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
        color: control.Style.primaryColor

        Root.Label {
            anchors.verticalCenterOffset: Devices.statusBarHeight/2
            anchors.centerIn: parent
            font.weight: Font.Medium
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
