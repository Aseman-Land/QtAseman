import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

AbstractStyle {
    id: dis

    padding {
        top: control.header? control.header.height : 0
        bottom: control.footer? control.footer.height : 0
    }

    Rectangle {
        anchors.fill: parent
        color: control.Style.backgroundColor
    }
}
