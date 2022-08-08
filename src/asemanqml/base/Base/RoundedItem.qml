import QtQuick 2.9
import QtGraphicalEffects 1.0

Item {
    id: dis
    data: [maskItem, clippedArea, opacityMask]

    property alias radius: maskItem.radius
    default property alias sceneData: sourceItem.data

    Rectangle {
        id: maskItem
        visible: false
        anchors.fill: parent
    }

    OpacityMask {
        id: opacityMask
        source: sourceItem
        maskSource: maskItem
        anchors.fill: parent
        cached: true
        visible: maskItem.radius != 0
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
