import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitHeight: 50

    Rectangle {
        anchors.fill: parent
        color: control.Style.primaryColor

        Root.Label {
            anchors.centerIn: parent
            font.bold: true
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
        opacity: 0.2
    }
}
