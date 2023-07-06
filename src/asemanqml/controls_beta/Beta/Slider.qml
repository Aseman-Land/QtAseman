import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

Control {
    id: dis
    styleFileName: "SliderStyle.qml"

    property real from: 0
    property real to: 100
    property real value: 0

    property alias pressedX: marea.mouseX
    property alias pressedY: marea.mouseY
    property alias pressed: marea.pressed
    property alias hovered: marea.containsMouse

    Keys.onLeftPressed: decrease()
    Keys.onRightPressed: increase()

    function decrease() {
        value = Math.min(to, Math.max(from, value - 0.1 * (to - from)));
    }
    function increase() {
        value = Math.min(to, Math.max(from, value + 0.1 * (to - from)));
    }

    MouseArea {
        id: marea
        anchors.fill: parent
        hoverEnabled: true
        onPressed: {
            dis.focus = true;
            dis.forceActiveFocus();
        }
    }
}
