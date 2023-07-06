import QtQuick 2.9
import AsemanQml.Controls.Beta 3.0
import AsemanQml.GraphicalEffects 2.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitWidth: 18
    implicitHeight: implicitWidth
    opacity: control.running ? 1 : 0
    Behavior on opacity { OpacityAnimator { duration: 250 } }


    Timer {
        interval: 80
        repeat: true
        running: control.running
        onTriggered: parent.rotation = (parent.rotation + 30) % 360
    }

    Repeater {
        model: 12
        Rectangle {
            property real size: parent.width

            width: 2
            height: size / 4
            radius: 16
            x: size/2 + size/2 * Math.sin(rotation * Math.PI/180).toFixed(12) - 1
            y: size/2 - size/2 * Math.cos(rotation * Math.PI/180).toFixed(12)
            rotation: index * 30
            antialiasing: true
            transformOrigin: Item.Top
            opacity: 1/16 * index + 4/16
            color: control.Style.foregroundColor
        }
    }
}
