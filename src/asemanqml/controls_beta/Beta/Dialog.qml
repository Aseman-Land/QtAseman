import QtQuick 2.15
import AsemanQml.Viewport 2.0
import AsemanQml.Controls.Beta 3.0
import "Private"

AbstractViewportScene {
    id: dis
    sceneComponent: freeSizeSceneItem
    styleFileName: "DialogStyle.qml"
    openToPrimaryViewport: true

    property string title
    property alias buttons: buttonsScene.data

    signal closed()
    signal rejected()
    signal accepted()

    onOpenedChanged: {
        if (!opened)
            closed()
    }

    function reject() {
        dialog.opened = false;
        dialog.rejected();
    }
    function accept() {
        dialog.opened = false;
        dialog.accepted();
    }

    data: [
        Item {
            id: buttonsScene
            visible: dis.item? true : false
        }
    ]

    Component {
        id: freeSizeSceneItem
        DialogScene {
            id: scene
            title: dis.title
            buttons: dis.buttons

            property variant prv

            Component.onCompleted: {
                item = delegate.createObject(Viewport.viewport, {"parent": scene.scene});

                prv.item = item;
                prv.setupViewportType(scene);
                dis.width = Qt.binding(function(){ return scene.width; });
                dis.height = Qt.binding(function(){ return scene.height; });
            }
            Component.onDestruction: {
                prv.item.destroy()
            }
        }
    }
}
