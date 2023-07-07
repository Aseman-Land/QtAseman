import QtQuick 2.9
import AsemanQml.Base 2.0
import AsemanQml.Controls.Beta 3.0

Item {
    id: hmb
    width: height
    height: Devices.standardTitleBarHeight
    y: View.statusBarHeight
    x: LayoutMirroring.enabled? parent.width - width : 0

    property alias buttonColor: menuIcon.color

    property alias ratio: menuIcon.ratio
    property alias pressed: marea.pressed

    signal clicked()

    LayoutMirroring.childrenInherit: true

    ItemDelegate {
        id: marea
        anchors.fill: parent
        onClicked: hmb.clicked()
    }

    MenuIcon {
        id: menuIcon
        anchors.centerIn: parent
    }
}
