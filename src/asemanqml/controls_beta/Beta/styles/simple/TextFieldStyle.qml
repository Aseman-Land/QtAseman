import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitHeight: (control.contentHeight <= 0? 33 : control.contentHeight + 18)
    implicitWidth: control.width

    padding {
        top: 9
        bottom: 10
        left: 4
        right: 4
    }

    NumberAnimation {
        id: scenePressAnim
        target: control
        property: "scale"
        easing.type: Easing.Linear
    }

    Root.Label {
        anchors.fill: parent
        leftPadding: dis.padding.left
        topPadding: dis.padding.top
        rightPadding: dis.padding.right
        bottomPadding: dis.padding.bottom
        font: control.font
        color: control.color
        opacity: 0.5
        horizontalAlignment: control.horizontalAlignment
        verticalAlignment: control.horizontalAlignment
        text: control.placeholderText
        visible: control.text.length == 0
    }

    Item {
        id: highlightArea
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 2

        Rectangle {
            anchors.fill: parent
            color: control.Style.foregroundColor
            opacity: 0.1
        }

        Rectangle {
            anchors.centerIn: parent
            height: parent.height
            width: control.activeFocus || marea.pressed? parent.width : 0
            radius: height/2
            color: control.Style.accentColor

            Behavior on width {
                NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
            }
        }
    }

    MouseArea {
        id: marea
        hoverEnabled: true
        acceptedButtons: Qt.RightButton
        cursorShape: Qt.IBeamCursor
        anchors.fill: parent
        onPressed: {
            let m = Math.max(width, height);
            var res = (m-4) / m;

            scenePressAnim.from = control.scale;
            scenePressAnim.to = Math.max(res, 0.95);
            scenePressAnim.start();
        }
        onReleased: {
            scenePressAnim.from = control.scale;
            scenePressAnim.to = 1;
            scenePressAnim.start();

            control.contextMenuRequest(mouseX, mouseY);
        }
    }
}
