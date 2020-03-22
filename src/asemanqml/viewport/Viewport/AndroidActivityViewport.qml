import QtQuick 2.0

AbstractViewportType {
    id: item

    background.scale: 1 - (ratio * 0.05)
    background.transformOrigin: Item.Bottom

    foreground.y: height * (1-ratio)

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 350 }
    }

    Rectangle {
        anchors.fill: parent
        z: -1
        color: "#000"
    }

    Rectangle {
        parent: item.backgroundScene
        anchors.fill: parent
        z: 100
        color: "#000"
        opacity: item.ratio * 0.3
    }
}
