import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import AsemanQml.GraphicalEffects 2.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitHeight: 52
    implicitWidth: 100

    Connections {
        target: control
        function onPressedChanged() {
            if (control.pressed) {
                highlightArea.pinX = control.pressed? control.pressedX : width/2;
                highlightArea.pinY = control.pressed? control.pressedY : height/2;
                highlightArea.opacity = 0.15;
                ratioAnim.start();

                let m = Math.max(width, height);
                var res = (m-4) / m;

                scenePressAnim.from = control.scene.scale;
                scenePressAnim.to = Math.max(res, 0.95);
                scenePressAnim.start();
            } else {
                opacityAnim.start();

                scenePressAnim.from = control.scene.scale;
                scenePressAnim.to = 1;
                scenePressAnim.start();
            }
        }
    }

    NumberAnimation {
        id: scenePressAnim
        target: control.scene
        property: "scale"
        easing.type: Easing.Linear
    }

    NumberAnimation {
        id: opacityAnim
        target: highlightArea
        property: "opacity"
        easing.type: Easing.Linear
        duration: 300
        from: 0.15; to: 0
    }
    NumberAnimation {
        id: ratioAnim
        target: highlightArea
        property: "width"
        easing.type: Easing.Linear
        duration: 300
        from: 0; to: dis.width*2
    }

    Rectangle {
        id: background
        anchors.fill: parent
        radius: control.radius
        color: control.Style.foregroundColor
        opacity: control.focusedInUsingKeyboard || control.hovered? 0.1 : 0
    }

    Item {
        id: highlightScene
        anchors.fill: parent
        clip: true
        visible: false

        Rectangle {
            id: highlightArea
            x: pinX - width/2
            y: pinY - height/2
            color: control.Style.foregroundColor
            height: width
            radius: height / 2

            property real pinX
            property real pinY
        }
    }

    OpacityMask {
        anchors.fill: parent
        maskSource: background
        source: highlightScene
    }
}
