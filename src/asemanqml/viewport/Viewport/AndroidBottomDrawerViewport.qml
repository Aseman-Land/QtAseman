import QtQuick 2.0
import QtGraphicalEffects 1.0

AbstractViewportType {
    id: item

    foreground.height: childItem? childItem.height : item.height
    foreground.y: height - foreground.height * ratio
    foreground.z: 10

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 350 }
    }

    Rectangle {
        anchors.fill: item.background
        color: "#000"
        opacity: item.ratio * 0.1
        visible: item.index <= 3
    }
}
