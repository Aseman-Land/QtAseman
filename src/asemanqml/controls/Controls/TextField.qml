import QtQuick 2.9
import AsemanQml.Base 2.0
import QtQuick.Controls 2.2 as QtControls

QtControls.TextField {
    id: field
    implicitWidth: -1

    property alias placeholder: pholder.text

    QtControls.Label {
        id: pholder
        opacity: minMode? 1 : 0.6
        scale: minMode? 0.8 : 1
        transformOrigin: LayoutMirroring.enabled? Item.Right : Item.Left
        y: minMode? field.topPadding - height : parent.height/2 - height/2 - (field.bottomPadding - field.topPadding)/2
        x: LayoutMirroring.enabled? parent.width - width - xPad : xPad
        color: field.focus? field.selectionColor : field.color

        readonly property bool minMode: field.text.length || field.preeditText.length
        property real xPad: minMode? 0 : LayoutMirroring.enabled? field.rightPadding : field.leftPadding

        Behavior on opacity {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }
        Behavior on scale {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }
        Behavior on y {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }
        Behavior on xPad {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }
    }
}
