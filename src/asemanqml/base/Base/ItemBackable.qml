import QtQuick 2.0
import AsemanQml.Base 2.0

Item {
    id: itemb

    property int layoutDirection: View.layoutDirection
    readonly property real closeRatio: marea.ratio
    property alias pressed: marea.pressed
    property alias handlerWidth: marea.width
    property alias active: marea.visible
    readonly property bool opened: marea.opened
    property int animationDuration: 300

    onCloseRatioChanged: {
        x = closeRatio * (layoutDirection == Qt.RightToLeft? -width : width)
        if(closeRatio == 1)
            closed()
    }

    signal closed()

    NumberAnimation {
        id: xAnim
        target: marea
        property: "ratio"
        easing.type: Easing.OutCubic
        duration: animationDuration
    }

    MouseArea {
        id: marea
        x: layoutDirection == Qt.RightToLeft? parent.width - width : 0
        z: 10000
        width: 30*Devices.density
        height: parent.height
        onPressed: {
            pinX = mouseX
            breakThePoint = false
        }
        onMouseXChanged: {
            var delta = mouseX - pinX
            if(Math.abs(delta) > 20*Devices.density)
                breakThePoint = true
            if(!breakThePoint)
                return

            var newX = itemb.x + delta
            if(layoutDirection == Qt.RightToLeft) {
                if(newX > 0) newX = 0
            } else {
                if(newX < 0) newX = 0
            }

            itemb.x = newX
            marea.ratio = getNewRatio()
        }
        onReleased: {
            var absX = itemb.x
            if(layoutDirection == Qt.RightToLeft)
                absX = -absX

            xAnim.from = getNewRatio()
            if(absX < itemb.width/4)
                xAnim.to = 0
            else {
                xAnim.to = 1
                opened = false
            }
            xAnim.start()
        }

        function getNewRatio() {
            var newRatio = itemb.x/itemb.width
            if(layoutDirection == Qt.RightToLeft)
                newRatio = -newRatio
            if(newRatio < 0)
                newRatio = 0
            return newRatio
        }

        property bool breakThePoint: false
        property bool opened: true
        property real ratio: 0
        property real pinX
    }
}
