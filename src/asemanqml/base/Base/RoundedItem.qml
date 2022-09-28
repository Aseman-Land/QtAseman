import QtQuick 2.9
import QtGraphicalEffects 1.0

Item {
    id: dis
    data: [maskItem, clippedArea, opacityMaskTop, opacityMaskBottom]

    property alias radius: maskItem.radius
    default property alias sceneData: sourceItem.data

    Rectangle {
        id: maskItem
        visible: false
        anchors.fill: parent
    }

    Item {
        id: opacityMaskTop
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: radius
        clip: true

        OpacityMask {
            source: sourceItem
            maskSource: maskItem
            width: maskItem.width
            height: maskItem.height
            anchors.top: parent.top
            cached: true
            visible: maskItem.radius != 0
        }
    }

    Item {
        id: opacityMaskBottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: radius
        clip: true

        OpacityMask {
            source: sourceItem
            maskSource: maskItem
            width: maskItem.width
            height: maskItem.height
            anchors.bottom: parent.bottom
            cached: true
            visible: maskItem.radius != 0
        }
    }

    Item {
        id: clippedArea
        height: dis.height - radius*2
        width: dis.width
        y: radius
        clip: true

        Item {
            id: sourceItem
            width: dis.width
            height: dis.height
            y: -dis.radius
        }
    }
}
