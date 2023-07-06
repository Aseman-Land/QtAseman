import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

Control {
    id: dis
    styleFileName: "FooterStyle.qml"
    data: [sceneItem, styleItem]
    focusableUsingKeyboard: false

    default property alias list: sceneItem.data
    property int currentIndex
    property bool interactive: true

    Item {
        id: sceneItem
        anchors.fill: parent
    }
}
