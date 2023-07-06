import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

AbstractViewportType {
    id: item

    fillForeground: true
    ratio: openRatio * mouseRatio

    background.x: LayoutMirroring.enabled? (foreground.x + item.width)/2 : (foreground.x - item.width)/2

    foreground.parent: dragScene
    foreground.anchors.top: foreground.parent.top
    foreground.anchors.bottom: foreground.parent.bottom
    foreground.x: foregroundX

    property real openRatio: open? 1 : 0
    property real mouseRatio: 1
    readonly property real foregroundX: (LayoutMirroring.enabled? -width : width) * (1-ratio)

    Behavior on openRatio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
    }

    Rectangle {
        parent: item.backgroundScene
        anchors.fill: parent
        z: 100
        color: "#000"
        opacity: item.openRatio * 0.4
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
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: item.gestureWidthIsNull? parent.width : item.gestureWidth
        drag {
            target: item.foreground
            axis: Drag.XAxis
            minimumX: LayoutMirroring.enabled? -item.width + 10 : 0
            maximumX: LayoutMirroring.enabled? 0 : item.width - 10
            filterChildren: true
            onActiveChanged: {
                if (dragArea.drag.active)
                    return;

                mouseRatio = (LayoutMirroring.enabled? item.width + foreground.x : item.width - foreground.x) / item.width
                foreground.x = Qt.binding( function(){ return foregroundX } )

                if (mouseRatio < 0.7) {
                    open = false
                } else {
                    mouseRatioAnim.from = mouseRatio
                    mouseRatioAnim.to = 1
                    mouseRatioAnim.start()
                }
            }
        }

        MouseArea {
            anchors.fill: parent
        }

        Item {
            id: dragScene
            width: item.width
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }
    }
}
