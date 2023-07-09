import QtQuick 2.12
import AsemanQml.Controls.Beta 3.0

Control {
    id: dis
    styleFileName: "ItemDelegateStyle.qml"
    data: [marea, scene, styleItem]

    property alias scene: scene
    default property alias items: scene.data

    property real radius: 8

    property alias pressedX: marea.mouseX
    property alias pressedY: marea.mouseY
    property alias pressed: marea.pressed
    property alias hovered: marea.containsMouse
    property alias pressAndHoldInterval: marea.pressAndHoldInterval
    property alias acceptedButtons: marea.acceptedButtons

    signal clicked(variant mouse)
    signal pressAndHold(variant mouse)

    Keys.onReturnPressed: dis.clicked()
    Keys.onEnterPressed: dis.clicked()
    Keys.onSpacePressed: dis.clicked()

    MouseArea {
        id: marea
        hoverEnabled: true
        anchors.fill: parent
        pressAndHoldInterval: 800
        onPressed: {
            dis.focus = true;
            dis.forceActiveFocus();
        }
        onClicked: function(mouse) { dis.clicked(mouse) }
        onPressAndHold: function(mouse) { dis.pressAndHold(mouse) }
    }

    Item {
        id: scene
        anchors.fill: parent
        anchors.topMargin: dis.styleItem.padding.top
        anchors.bottomMargin: dis.styleItem.padding.bottom
        anchors.leftMargin: dis.styleItem.padding.left
        anchors.rightMargin: dis.styleItem.padding.right
    }
}
