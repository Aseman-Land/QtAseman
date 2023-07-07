import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import AsemanQml.GraphicalEffects 2.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitHeight: 44
    implicitWidth: contentRow.width + 40

    Connections {
        target: control
        function onPressedChanged() {
            if (control.pressed) {
                highlightArea.pinX = control.pressed? control.pressedX : width/2;
                highlightArea.pinY = control.pressed? control.pressedY : height/2;
                highlightArea.opacity = 0.15;
                ratioAnim.start();
            } else {
                opacityAnim.start();
            }
        }
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
        color: control.flat? "transparent" : control.highlighted && control.enabled? control.Style.accentColor : "transparent"
        radius: control.radius

        Rectangle {
            anchors.fill: parent
            opacity: (!control.flat && !control.highlighted? 0.2 : !control.enabled? (control.highlighted? 0.3 : 0.2) : 0) + (control.pressed || control.focusedInUsingKeyboard || control.hovered? 0.1 : 0)
            color: control.Style.foregroundColor
            radius: control.radius
        }
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

    Row {
        id: contentRow
        anchors.centerIn: parent
        spacing: 4
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

        Root.Icon {
            color: mainText.color
            font.pixelSize: control.iconPixelSize
            text: control.icon
            visible: text.length
        }

        Root.Label {
            id: mainText
            color: control.highlighted && control.flat? control.Style.accentColor : control.highlighted? control.Style.accentTextColor : control.Style.foregroundColor
            text: control.text
            visible: text.length
        }
    }
}
