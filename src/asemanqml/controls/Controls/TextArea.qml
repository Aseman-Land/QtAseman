import QtQuick 2.9
import AsemanQml.Base 2.0
import QtQuick.Controls 2.2 as QtControls

QtControls.TextArea {
    id: field
    implicitWidth: -1

    property alias placeholder: pholder.text

    QtControls.Label {
        id: pholder
        opacity: field.text.length || field.preeditText.length? 1 : 0.6
        scale: field.text.length || field.preeditText.length? 0.7 : 1
        transformOrigin: LayoutMirroring.enabled? Item.Left : Item.Right
        y: field.text.length || field.preeditText.length? -height/2 : field.font.pixelSize/2 - height/2 + 8*Devices.density
        x: LayoutMirroring.enabled? 0 : parent.width - width

        Behavior on opacity {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }
        Behavior on scale {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }
        Behavior on y {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }
    }
}
