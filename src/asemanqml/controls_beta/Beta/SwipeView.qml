import QtQuick 2.15
import AsemanQml.Controls.Beta 3.0

Control {
    id: dis
    styleFileName: "SwipeViewStyle.qml"
    focusableUsingKeyboard: false
    focusable: false
    data: [sceneItem, styleItem]

    default property alias list: sceneItem.data
    property int currentIndex
    property bool interactive: true

    Item {
        id: sceneItem
        anchors.fill: parent
    }
}
