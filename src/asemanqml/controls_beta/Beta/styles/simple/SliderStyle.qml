import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitHeight: 28

    Connections {
        target: control
        function onPressedXChanged() {
            if (!control.pressed)
                return;

            var val = ((control.pressedX - background.x) * (control.to - control.from) / background.width) + control.from;
            control.value = Math.min(control.to, Math.max(control.from, val));
        }
    }

    Rectangle {
        anchors.fill: parent
        radius: 6
        color: control.Style.foregroundColor
        opacity: control.focusedInUsingKeyboard? 0.1 : 0
    }

    Rectangle {
        id: background
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 12
        height: 5
        opacity: 0.3
        radius: height/2
        color: control.Style.foregroundColor
    }

    Rectangle {
        id: fillArea
        anchors.left: background.left
        anchors.top: background.top
        anchors.bottom: background.bottom
        radius: height/2
        color: control.Style.accentColor
        width: radius*2 + (background.width - radius*2) * ((control.value + control.from) / (control.to - control.from))
    }

    Rectangle {
        anchors.horizontalCenter: fillArea.right
        anchors.horizontalCenterOffset: -fillArea.radius
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 4
        width: height
        radius: height/2
        color: control.Style.accentColor
        scale: {
            if (!control.pressed)
                return 1;

            let m = Math.max(width, height);
            var res = (m-4) / m;
            return Math.max(res, 0.95);
        }

        Behavior on scale {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }

        Rectangle {
            anchors.fill: parent
            anchors.margins: 2
            radius: height/2
            color: control.Style.backgroundColor
        }
    }
}
