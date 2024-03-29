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
                highlightArea.opacity = 0.1;
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

    Item {
        id: background
        anchors.fill: parent
        visible: false

        Rectangle {
            anchors.fill: parent
        }
    }

    Rectangle {
        anchors.fill: background
        opacity: control.pressed || control.focusedInUsingKeyboard || control.hovered? 0.05 : 0
        color: control.Style.foregroundColor
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

    Column {
        id: contentRow
        anchors.centerIn: parent
        spacing: 4
        scale: {
            var value = 0.8;
            if (!control.pressed)
                return value;

            let m = Math.max(width, height);
            var res = (m-4) / m;
            return Math.max(res, 0.95) * value;
        }

        Behavior on scale {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }

        Root.Icon {
            anchors.horizontalCenter: parent.horizontalCenter
            color: mainText.color
            font.pixelSize: control.iconPixelSize
            text: control.icon
            visible: text.length
        }

        Root.Label {
            id: mainText
            anchors.horizontalCenter: parent.horizontalCenter
            color: control.parent.ListView.isCurrentItem? control.Style.accentColor : control.Style.foregroundColor
            text: control.text
            visible: text.length
        }
    }
}
