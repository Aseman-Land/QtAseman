import QtQuick 2.0
import AsemanQml.GraphicalEffects 2.0

Item {
    id: item

    property alias radius: blur.radius
    property alias color: shadowMask.color
    property real horizontalOffset
    property real verticalOffset
    property bool cached: true
    property alias source: shadowArea.maskSource

    FastBlur {
        id: blur
        x: parent.width/2 - width/2 + item.horizontalOffset
        y: parent.height/2 - height/2 + item.verticalOffset
        width: shadowScene.width
        height: shadowScene.height
        source: shadowScene
        cached: item.cached
    }

    Item {
        id: shadowScene
        anchors.fill: parent
        anchors.margins: -item.radius*2
        visible: false

        Item {
            width: item.width
            height: item.height
            anchors.centerIn: parent

            OpacityMask {
                id: shadowArea
                anchors.fill: parent
                source: shadowMask
                cached: item.cached
            }

            Rectangle {
                id: shadowMask
                color: "#333"
                anchors.fill: parent
                visible: false
            }
        }
    }
}
