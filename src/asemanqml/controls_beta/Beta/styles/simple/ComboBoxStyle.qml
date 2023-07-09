import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import AsemanQml.GraphicalEffects 2.0
import AsemanQml.MaterialIcons 2.0
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

    Item {
        id: background
        anchors.fill: parent
        visible: false

        Rectangle {
            anchors.fill: parent
            radius: control.radius
        }
    }

    Rectangle {
        anchors.fill: background
        color: "transparent"
        radius: control.radius
        opacity: control.focusedInUsingKeyboard? 0.5 : 0.1
        border.width: 1
        border.color: control.focusedInUsingKeyboard? control.Style.accentColor : control.Style.foregroundColor
    }

    Rectangle {
        anchors.fill: background
        opacity: control.pressed || control.focusedInUsingKeyboard || control.hovered? 0.1 : 0
        color: control.Style.foregroundColor
        radius: control.radius
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
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
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

        Root.Label {
            id: mainText
            color: control.Style.foregroundColor
            text: control.displayText
            visible: text.length
        }
    }

    Root.Icon {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 5
        text: MaterialIcons.mdi_menu_down
        font.pixelSize: 20
    }
}
