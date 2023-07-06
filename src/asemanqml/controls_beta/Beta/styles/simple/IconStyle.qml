import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import AsemanQml.MaterialIcons 2.0

AbstractStyle {
    id: dis
    implicitHeight: control.height
    implicitWidth: control.width
    font.family: MaterialIcons.family
    extra: {
        "lineHeight": 1,
        "lineHeightMode": Text.ProportionalHeight,
    }
}
