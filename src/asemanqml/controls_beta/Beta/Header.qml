import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

Control {
    id: dis
    data: [scene, styleItem]
    styleFileName: "HeaderStyle.qml"
    focusableUsingKeyboard: false

    property alias scene: scene
    default property alias items: scene.data

    property string title: parent && parent.title != undefined? parent.title : ""

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
