import QtQuick 2.0
import AsemanQml.Base 2.0
import QtQuick.Controls 2.0

Page {

    readonly property bool landscape: !Devices.isDesktop && width>=height
    property alias footerItem: _footer

    Rectangle {
        id: _footer
        width: landscape? View.navigationBarHeight : parent.width
        height: landscape? parent.height : View.navigationBarHeight
        x: 0
        y: landscape? 0 : parent.height - height
        color: "#000"
    }

    Item {
        id: scene
        x: landscape? _footer.width : 0
        y: 0
        width: landscape? parent.width - x : parent.width
        height: landscape? parent.height : parent.height - _footer.height
        clip: true
    }

    default property alias sceneData: scene.data
}
