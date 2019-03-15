import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    data: [maskItem, sourceItem, opacityMask]

    property alias radius: maskItem.radius
    default property alias sceneData: sourceItem.data

    Rectangle {
        id: maskItem
        visible: false
        anchors.fill: parent
    }

    Item {
        id: sourceItem
        anchors.fill: parent
        opacity: maskItem.radius == 0? 1 : 0
    }

    OpacityMask {
        id: opacityMask
        source: sourceItem
        maskSource: maskItem
        anchors.fill: parent
        cached: true
        visible: maskItem.radius != 0
    }
}
