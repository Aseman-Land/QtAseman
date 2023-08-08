import QtQuick 2.15
import AsemanQml.Viewport 2.0
import AsemanQml.Controls.Beta 3.0
import "Private"

AbstractViewportScene {
    id: dis
    sceneComponent: freeSizeSceneItem
    styleFileName: "DialogStyle.qml"
    openToPrimaryViewport: true

    property Component sceneStyleComponent
    property string sceneStyleFileName: "DialogSceneStyle.qml"

    property string title
    property alias buttons: buttonsScene.data

    property variant leftPadding
    property variant rightPadding
    property variant topPadding
    property variant bottomPadding

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
            styleComponent: dis.sceneStyleComponent
            styleFileName: dis.sceneStyleFileName

            leftPadding: dis.leftPadding != null? dis.leftPadding : styleItem.padding.left
            rightPadding: dis.rightPadding != null? dis.rightPadding : styleItem.padding.right
            topPadding: dis.topPadding != null? dis.topPadding : styleItem.padding.top
            bottomPadding: dis.bottomPadding != null? dis.bottomPadding : styleItem.padding.bottom

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
