import QtQuick 2.0
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    fillForeground: true
    ratio: openRatio * mouseRatio

    background.scale: 1 - (ratio * 0.05)
    background.transformOrigin: Item.Bottom

    foreground.z: 10
    foreground.y: height * (1-ratio)
    foregroundScene.anchors.topMargin: -Devices.statusBarHeight

    property real openRatio: open? 1 : 0
    property real mouseRatio: 1

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

    Item {
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            preventStealing: true
            visible: item.gestureWidthIsNull || item.gestureWidth
            onMouseYChanged: {
                var ratio = 1 - ((mouseY - pinY) / item.foreground.height);
                if (ratio < 0.01)
                    ratio = 0.01;
                if (ratio > 1)
                    ratio = 1;

                mouseRatio = ratio;
            }
            onPressed: pinY = mouseY
            onReleased: {
                if (mouseRatio < 0.7) {
                    open = false
                } else {
                    mouseRatioAnim.from = mouseRatio
                    mouseRatioAnim.to = 1
                    mouseRatioAnim.start()
                }
            }

            property real pinY
        }
    }
}
