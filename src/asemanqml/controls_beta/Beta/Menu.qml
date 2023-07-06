import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

MenuPopup {
    id: dis
    height: mainColumn.height
    styleFileName: "MenuStyle.qml"
    delegate: Item {
        id: listv

        Component.onCompleted: {
            for (var i=0; i<mainColumn.data.length; i++) {
                var b = mainColumn.data[i];
                if (b.clicked) {
                    b.clicked.connect(dis.close);
                }
            }
        }
    }

    default property alias sceneData: mainColumn.data

    data: [
        Scene {
            parent: dis.item? dis.item : dis
            visible: dis.item? true : false
            width: mainColumn.width
            height: mainColumn.height

            Column {
                id: mainColumn
                width: dis.item? dis.item.width : 200
            }
        }
    ]
}
