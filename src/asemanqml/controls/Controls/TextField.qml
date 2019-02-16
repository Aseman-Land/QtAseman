import QtQuick 2.7
import AsemanQml.Base 2.0
import QtQuick.Controls 2.2 as QtControls
import QtQuick.Layouts 1.3 as QtLayouts
import QtQuick.Controls.Material 2.1

QtControls.TextField {
    id: field
    implicitWidth: -1

    property alias placeholder: pholder.text
    property alias cursorParent: cursor.cursorParent

    QtControls.Label {
        id: pholder
        opacity: field.text.length || field.preeditText.length? 1 : 0.6
        scale: field.text.length || field.preeditText.length? 0.7 : 1
        transformOrigin: View.defaultLayout? Item.Left : Item.Right
        y: field.text.length || field.preeditText.length? -height/2 : parent.height/2 - height/2 - 4*Devices.density
        x: View.defaultLayout? 0 : parent.width - width

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

    TextCursorArea { id: cursor; active: true}
}
