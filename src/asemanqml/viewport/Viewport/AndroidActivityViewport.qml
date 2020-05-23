import QtQuick 2.0
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    fillForeground: true
    ratio: openRatio * mouseRatio

    background.scale: 1 - (realRatio * 0.05)
    background.transformOrigin: Item.Bottom
    background.clip: true

    foreground.z: 10
    foreground.y: height * (1-ratio)
    foreground.parent: dragArea

    property real openRatio: open? 1 : 0
    property real mouseRatio: 1
    readonly property real realRatio: 1 - foreground.y / dragArea.height

    Behavior on openRatio {
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

    NumberAnimation {
        id: mouseRatioAnim
        target: item
        property: "mouseRatio"
        easing.type: Easing.OutCubic
        duration: 300
    }

    MouseArea {
        id: dragArea
        anchors.left: parent.left
        anchors.right: parent.right
        height: item.gestureWidthIsNull? item.height : item.gestureWidth
        drag {
            target: item.foreground
            axis: Drag.YAxis
            minimumY: 0
            maximumY: item.height - 10
            filterChildren: true
            onActiveChanged: {
                if (dragArea.drag.active)
                    return;

                mouseRatio = realRatio
                foreground.y = Qt.binding( function() { return height * (1-ratio); } )
                if (realRatio < 0.7) {
                    open = false
                } else {
                    mouseRatioAnim.from = realRatio
                    mouseRatioAnim.to = 1
                    mouseRatioAnim.start()
                }
            }
        }

        MouseArea {
            anchors.fill: parent
        }
    }
}
