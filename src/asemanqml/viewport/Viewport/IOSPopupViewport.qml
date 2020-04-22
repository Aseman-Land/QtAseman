import QtQuick 2.0
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    fillForeground: true
    ratio: openRatio * mouseRatio

    background.transformOrigin: iosIndex < 2? Item.Center : Item.Top
    background.scale: 1 - (ratio * topPadSize / height)
    background.radius: 10 * Devices.density

    foreground.parent: column
    foreground.anchors.top: foreground.parent.top
    foreground.anchors.topMargin: foreground.radius + item.height
    foreground.height: item.height - (item.iosIndex * topPadSize ) + foreground.radius
    foreground.radius: 10 * Devices.density
    foreground.z: 10
    foregroundScene.anchors.bottomMargin: foreground.radius
    foregroundScene.anchors.topMargin: -Devices.statusBarHeight

    readonly property bool isIOSPopup: true
    readonly property int iosIndex: {
        if (!list)
            return 0;
        for (var i=list.count-1; i>=0; i--)
        {
            if (!list.at(i).isIOSPopup)
                return index - i - 1
        }
        return index
    }

    readonly property real topPadSize: Math.max(20 * Devices.density, Devices.statusBarHeight) + 5 * Devices.density
    property real openRatio: open? 1 : 0
    property real mouseRatio: 1

    onOpenChanged: {
        if (open)
            return;

        var mr = mouseRatio
        ratio = Qt.binding( function(){ return openRatio * mr } )
        flickAnim.from = flick.contentY
        flickAnim.to = 0
        flickAnim.start()
    }

    onHeightChanged: flick.contentY = (open? item.foreground.height : 0)

    Behavior on openRatio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 350 }
    }

    Rectangle {
        anchors.fill: parent
        z: -1
        color: "#000"
    }

    NumberAnimation {
        id: flickAnim
        target: flick
        property: "contentY"
        easing.type: Easing.OutCubic
        duration: 350
        from: 0
        to: item.foreground.height
        Component.onCompleted: Tools.jsDelayCall(1, start)
    }

    NumberAnimation {
        id: mouseRatioAnim
        target: item
        property: "mouseRatio"
        easing.type: Easing.OutCubic
        duration: 300
    }

    Flickable {
        id: flick
        anchors.left: parent.left
        anchors.right: parent.right
        height: item.gestureWidthIsNull || item.gestureWidth <= 0? item.height : item.gestureWidth + topPadSize + foreground.radius
        flickableDirection: Flickable.VerticalFlick
        contentWidth: column.width
        contentHeight: item.foreground.height + height
        boundsBehavior: Flickable.StopAtBounds
        interactive: item.gestureWidthIsNull || item.gestureWidth
        rebound: Transition {
            NumberAnimation {
                properties: "x,y"
                duration: 0
            }
        }
        onContentYChanged: if (dragging) mouseRatio = flick.contentY / item.foreground.height
        onDraggingChanged: {
            if (dragging)
                return;

            if (mouseRatio < 0.7) {
                open = false
            } else {
                mouseRatioAnim.from = mouseRatio
                mouseRatioAnim.to = 1
                mouseRatioAnim.start()

                flickAnim.from = flick.contentY
                flickAnim.to = item.foreground.height
                flickAnim.start()
            }
        }

        Item {
            id: column
            width: item.width
            height: item.height + item.foreground.height
        }
    }

    Rectangle {
        parent: item.backgroundScene
        anchors.fill: parent
        z: 100
        color: "#000"
        opacity: item.ratio * 0.2
    }
}
