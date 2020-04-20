import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.3
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    foreground.height: foregroundItem? foregroundItem.height : item.height
    foreground.y: height - foreground.height * ratio
    foreground.z: 10
    foregroundScene.color: "transparent"
    foreground.parent: column
    foreground.anchors.bottom: foreground.parent.bottom
    foreground.anchors.bottomMargin: -foreground.radius
    foregroundScene.anchors.bottomMargin: foreground.radius

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

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 350 }
    }

    Rectangle {
        anchors.fill: item.background
        color: "#000"
        opacity: item.ratio * 0.3
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

    Page {
        width: item.foreground.width
        height: flick.contentY
        anchors.bottom: parent.bottom
        z: 5
        clip: true
    }

    Flickable {
        id: flick
        anchors.fill: parent
        z: 6
        flickableDirection: Flickable.VerticalFlick
        contentWidth: column.width
        contentHeight: column.height
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
            width: flick.width
            height: flick.height + item.foreground.height
        }
    }
}
