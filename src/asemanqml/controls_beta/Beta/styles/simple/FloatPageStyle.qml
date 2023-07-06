import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

AbstractViewportType {
    id: item

    fillForeground: true
    ratio: openRatio * mouseRatio

    background.scale: Math.min(1, iosBelowIndex < 2 && !tabletMode? 1 - (realRatio * ((topPadSize -  background.radius) * 2) / height) : 1)
    background.transformOrigin: Item.Center
    background.radius: tabletMode? 0 : 10 * Devices.density

    foreground.z: 10
    foreground.y: height * (1-ratio)
    foreground.parent: dragArea
    foreground.height: foregroundHeight + foreground.radius
    foreground.radius: 10 * Devices.density
    foreground.transformOrigin: Item.Center
    foreground.scale: 1 - foregroundScale * ((topPadSize -  background.radius) * 2) / height
    foregroundScene.anchors.topMargin: -Devices.statusBarHeight
    foregroundScene.anchors.bottomMargin: foreground.radius

    readonly property real topPadSize: Math.max(20 * Devices.density, Devices.statusBarHeight + 20 * Devices.density)
    property real openRatio: open? 1 : 0
    property real mouseRatio: 1
    readonly property real foregroundScale: nextItem? nextItem.realRatio : 0
    readonly property real foregroundHeight: item.height - topPadSize
    readonly property real realRatio: 1 - foreground.y / foreground.height
    readonly property bool tabletMode: !item.maximumWidthIsNull && item.maximumWidth != 0

    readonly property bool isIOSPopup: true
    readonly property Item nextItem: {
        if (index==0 || !list || list.count <= index)
            return null;
        if (list.at(index).isIOSPopup)
            return list.at(index);
        return null;
    }
    readonly property int iosBelowIndex: {
        if (index==0 || !list || list.count === 0)
            return 0;

        var start = Math.min(index, list.count-1);
        for (var i=start; i>=0; i--)
            if (!list.at(i).isIOSPopup)
                return start - i - 1;

        return index;
    }

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
        width: tabletMode? item.maximumWidth : item.width
        x: Math.floor(item.width/2 - foreground.width/2)
        y: Math.floor(topPadSize * (1 - foregroundScale))
        height: item.gestureWidthIsNull? (item.height - topPadSize) : item.gestureWidth
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
                foreground.y = Qt.binding( function() { return foregroundHeight * (1-ratio); } )
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
