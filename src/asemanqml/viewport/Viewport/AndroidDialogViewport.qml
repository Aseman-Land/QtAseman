import QtQuick 2.0
import QtGraphicalEffects 1.0
import AsemanQml.Modern 2.0

AbstractViewportType {
    id: item

    foreground.height: foregroundItem? foregroundItem.height : item.height
    foreground.width: foregroundItem? foregroundItem.width : item.width
    foreground.scale: 0.8 + ratio * 0.2
    foreground.opacity: ratio
    foreground.anchors.centerIn: foreground.parent
    foreground.z: 10

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
    }

    Rectangle {
        anchors.fill: item.background
        color: "#000"
        opacity: item.ratio * 0.2
        visible: item.ratio

        MouseArea {
            anchors.fill: parent
            onClicked: item.open = false
        }
    }

    FastRectengleShadow {
        scale: item.foreground.scale
        anchors.fill: item.foreground
        z: 5
        radius: 32
        opacity: 0.6 * item.ratio
    }
}
