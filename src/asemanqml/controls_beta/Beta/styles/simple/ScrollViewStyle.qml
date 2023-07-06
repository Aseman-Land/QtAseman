import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import "../.." as Root

AbstractStyle {
    id: dis
    data: [verticalScrollBar]

    property Root.ScrollBar verticalScrollBar: Root.ScrollBar {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        z: 1000
        flickArea: control.flickArea
    }
}
