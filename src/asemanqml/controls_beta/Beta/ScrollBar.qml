import QtQuick 2.9
import AsemanQml.Controls.Beta 3.0
import AsemanQml.Controls.Beta 3.0

Control {
    id: dis
    styleFileName: "ScrollBarStyle.qml"
    focusableUsingKeyboard: false
    focusable: false

    property Flickable flickArea
    property int orientation: Qt.Vertical
    property color color: dis.Style.foregroundColor
    property bool forceVisible: false
}
