import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

Control {
    id: dis
    styleFileName: "ProgressBarStyle.qml"
    focusableUsingKeyboard: false
    focusable: false

    property real from: 0
    property real to: 100
    property real value: 0
    property bool indeterminate
}
