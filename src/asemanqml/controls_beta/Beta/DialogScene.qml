import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

Scene {
    id: dis
    data: [styleItem, scene]
    styleFileName: "DialogSceneStyle.qml"

    property real leftPadding: dis.styleItem.padding.left
    property real rightPadding: dis.styleItem.padding.right
    property real topPadding: dis.styleItem.padding.top
    property real bottomPadding: dis.styleItem.padding.bottom

    property string title
    property variant buttons
    property Item item

    property alias scene: scene
    default property alias items: scene.data

    Item {
        id: scene
        anchors.fill: parent
        anchors.topMargin: dis.topPadding
        anchors.bottomMargin: dis.bottomPadding
        anchors.leftMargin: dis.leftPadding
        anchors.rightMargin: dis.rightPadding
        z: 10
    }
}
