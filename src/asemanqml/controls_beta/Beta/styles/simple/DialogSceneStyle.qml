import QtQuick 2.15
import AsemanQml.Base 2.0
import AsemanQml.Controls.Beta 3.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitWidth: (control.item? control.item.width : 0) + padding.left + padding.right
    implicitHeight: (control.item? control.item.height : 0) + padding.top + padding.bottom

    padding {
        top: control.title.length? headerLabel.height + 10 * Devices.density : 20 * Devices.density
        left: 20 * Devices.density
        right: 20 * Devices.density
        bottom: repeater.count? buttonsRow.height + 20 * Devices.density : 20 * Devices.density
    }

    Rectangle {
        anchors.fill: parent
        opacity: 0.5
        color: control.Style.baseColor
    }

    Root.Label {
        id: headerLabel
        y: 10 * Devices.density
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20 * Devices.density
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        height: Devices.standardTitleBarHeight
        text: control.title
        font.pixelSize: 12 * Devices.fontDensity
        font.weight: Font.Medium
    }

    RowLayout {
        id: buttonsRow
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20 * Devices.density
        anchors.rightMargin: 20 * Devices.density
        anchors.bottomMargin: 10 * Devices.density
        layoutDirection: Qt.RightToLeft

        Repeater {
            id: repeater
            model: {
                var res = new Array;
                for (var i=control.buttons.length-1 ;i>=0; i--) {
                    var item = control.buttons[i];
                    if (item.transformOrigin == undefined)
                        continue;

                    res[res.length] = item;
                }
                return res;
            }
            delegate: Item {
                id: item
                implicitWidth: modelData.width
                implicitHeight: modelData.height
                Layout.fillWidth: modelData.Layout.fillWidth
                Layout.fillHeight: modelData.Layout.fillHeight
                Layout.preferredWidth: modelData.Layout.preferredWidth
                Layout.preferredHeight: modelData.Layout.preferredHeight

                property Item backupParent
                Component.onCompleted: {
                    backupParent = modelData.parent;
                    modelData.parent = item;
                }
                Component.onDestruction: modelData.parent = backupParent
            }
        }
    }
}
