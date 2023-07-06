import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

RadioControl {
    id: dis
    styleFileName: "RadioButtonStyle.qml"

    property string text

    property alias pressedX: marea.mouseX
    property alias pressedY: marea.mouseY
    property alias pressed: marea.pressed
    property alias hovered: marea.containsMouse

    signal clicked()
    signal toggled()

    Keys.onSpacePressed: toggle()
    Keys.onReturnPressed: toggle()
    Keys.onEnterPressed: toggle()

    function toggle() {
        dis.checked = true;
        toggled();
    }

    MouseArea {
        id: marea
        hoverEnabled: true
        anchors.fill: parent
        onPressed: {
            dis.focus = true;
            dis.forceActiveFocus();
        }
        onClicked: {
            toggle();
            dis.clicked();
        }
    }
}
