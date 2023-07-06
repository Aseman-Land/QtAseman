import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

AbstractStyle {
    id: dis
    implicitHeight: control.height
    implicitWidth: control.width
    extra: {
        "lineHeight": 1,
        "lineHeightMode": Text.ProportionalHeight,
    }
}
