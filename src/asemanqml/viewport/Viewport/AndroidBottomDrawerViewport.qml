import QtQuick 2.0
import QtGraphicalEffects 1.0

AbstractViewportType {
    id: item

    foreground.height: foregroundItem? foregroundItem.height : item.height
    foreground.y: height - foreground.height * ratio
    foreground.z: 10

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 350 }
    }

    MouseArea {
        parent: item.background
        anchors.fill: parent
        hoverEnabled: true
        onClicked: item.open = false
    }

    Rectangle {
        anchors.fill: item.background
        color: "#000"
        opacity: item.ratio * 0.1
        visible: item.index <= 3
    }
}
