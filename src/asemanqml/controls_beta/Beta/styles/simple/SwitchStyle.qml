import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import AsemanQml.MaterialIcons 2.0
import AsemanQml.GraphicalEffects 2.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitHeight: contentRow.height + 14
    implicitWidth: contentRow.width + 14

    property bool delegateMode

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
        radius: 6
        color: control.Style.foregroundColor
        opacity: control.focusedInUsingKeyboard? 0.1 : 0
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
        spacing: 10
        scale: {
            if (!control.pressed)
                return 1;

            let m = Math.max(width, height);
            var res = (m-4) / m;
            return Math.max(res, 0.95);
        }
        layoutDirection: delegateMode? Qt.RightToLeft : Qt.LeftToRight

        Behavior on scale {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }

        Item {
            width: 36
            height: 22

            Rectangle {
                id: bilbil
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                height: parent.height
                radius: height/2
                color:  control.checked? control.Style.accentColor : control.Style.foregroundColor
                opacity: control.checked? 1 : 0.3

                Behavior on color {
                    ColorAnimation { easing.type: Easing.OutCubic; duration: 200 }
                }
                Behavior on opacity {
                    NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
                }
            }

            Rectangle {
                height: parent.height - 4
                anchors.verticalCenter: parent.verticalCenter
                x: control.checked? (control.LayoutMirroring.enabled? 2 : parent.width - width - 2) : (control.LayoutMirroring.enabled? parent.width - width - 2 : 2)
                width: height
                radius: height / 2
                color: control.Style.backgroundColor

                Behavior on opacity {
                    NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
                }

                Behavior on x {
                    NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
                }
            }
        }

        Root.Label {
            anchors.verticalCenter: parent.verticalCenter
            color: control.Style.foregroundColor
            text: control.text
            visible: text.length
        }
    }
}
