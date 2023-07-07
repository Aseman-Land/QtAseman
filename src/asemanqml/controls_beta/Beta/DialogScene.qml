import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

Scene {
    id: dis
    data: [styleItem, scene]
    styleFileName: "DialogSceneStyle.qml"

    property string title
    property variant buttons
    property Item item

    property alias scene: scene
    default property alias items: scene.data

    Item {
        id: scene
        anchors.fill: parent
        anchors.topMargin: dis.styleItem.padding.top
        anchors.bottomMargin: dis.styleItem.padding.bottom
        anchors.leftMargin: dis.styleItem.padding.left
        anchors.rightMargin: dis.styleItem.padding.right
        z: 10
    }
}
