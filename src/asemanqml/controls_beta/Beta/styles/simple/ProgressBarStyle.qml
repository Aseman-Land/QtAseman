import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitHeight: 7

    Rectangle {
        anchors.fill: parent
        opacity: 0.3
        radius: height/2
        color: control.Style.foregroundColor
    }

    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        radius: height/2
        color: control.Style.accentColor
        width: radius*2 + (dis.width - radius*2) * ((control.value + control.from) / (control.to - control.from))
    }
}
