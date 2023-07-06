import QtQuick 2.0
import AsemanQml.GraphicalEffects 2.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

AbstractViewportType {
    id: item

    foreground.x: foregroundItem? -foregroundItem.x : 0
    foreground.height: foregroundItem? foregroundItem.height : item.height
    foreground.z: 10
    foreground.parent: dragArea
    foregroundScene.color: "transparent"

    property real openRatio: open? 1 : 0

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 350 }
    }

    Rectangle {
        anchors.fill: item.background
        color: "#000"
        opacity: item.ratio * 0.3
    }

    NumberAnimation {
        id: foregroundAnim
        target: foreground
        property: "y"
        easing.type: Easing.OutCubic
        duration: 300
    }

    Item {
        width: foregroundItem? foregroundItem.width : item.width
        x: foregroundItem? foregroundItem.x : 0
        height: item.height - dragArea.y - item.foreground.y
        anchors.bottom: parent.bottom
        z: 5
        clip: true

        FastBlur {
            x: foregroundItem? -foregroundItem.x : 0
            anchors.bottom: parent.bottom
            height: item.background.height
            width: item.background.width
            radius: 64
            cached: true
            source: item.background
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
    }

    MouseArea {
        anchors.fill: parent
        visible: item.touchToCloseIsNull || item.touchToClose
        onClicked: open = false
    }

    MouseArea {
        id: dragArea
        width: foregroundItem? foregroundItem.width : item.width
        x: foregroundItem? foregroundItem.x : 0
        height: item.gestureWidthIsNull? item.foreground.height : item.gestureWidth
        y: parent.height - item.foreground.height * item.ratio
        z: 10
        drag {
            target: item.foreground
            axis: Drag.YAxis
            minimumY: 0
            maximumY: item.height - 10
            filterChildren: true
            onActiveChanged: {
                if (dragArea.drag.active)
                    return;

                var ratio = 1 - foreground.y / dragArea.height
                if (ratio < 0.7) {
                    open = false
                } else {
                    foregroundAnim.from = foreground.y
                    foregroundAnim.to = 0
                    foregroundAnim.start()
                }
            }
        }

        MouseArea {
            anchors.fill: parent
        }
    }
}
