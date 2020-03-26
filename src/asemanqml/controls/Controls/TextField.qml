import QtQuick 2.9
import AsemanQml.Base 2.0
import QtQuick.Controls 2.2 as QtControls

QtControls.TextField {
    id: field
    implicitWidth: -1

    property alias placeholder: pholder.text

    QtControls.Label {
        id: pholder
        opacity: field.text.length || field.preeditText.length? 1 : 0.6
        scale: field.text.length || field.preeditText.length? 0.8 : 1
        transformOrigin: View.defaultLayout? Item.Left : Item.Right
        y: field.text.length || field.preeditText.length? -height/2 : parent.height/2 - height/2 - 4*Devices.density
        x: View.defaultLayout? 0 : parent.width - width
        color: field.focus? field.selectionColor : field.color

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
