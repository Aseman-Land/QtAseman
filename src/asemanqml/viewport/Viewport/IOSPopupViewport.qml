import QtQuick 2.0
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    ratio: openRatio * mouseRatio

    background.transformOrigin: index < 2? Item.Center : Item.Top
    background.scale: 1 - (ratio * topPadSize / height)
    background.radius: Devices.isAndroid? 0 : 10 * Devices.density

    foreground.y: height * (1-ratio) + (height - foreground.height)
    foreground.height: item.height - (item.index * topPadSize )
    foreground.radius: Devices.isAndroid? 0 : 10 * Devices.density

    readonly property real topPadSize: 25 * Devices.density
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
        opacity: item.ratio * 0.2
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
            rotation: layoutDirection==Qt.LeftToRight? 0 : 180
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
