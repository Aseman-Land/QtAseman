import QtQuick 2.0
import AsemanQml.Base 2.0

Item {
    id: base
    anchors.fill: parent
    data: [scene]

    default property alias contents: back.data

    property Item delegateItem
    property Component delegate

    onDelegateChanged: if(delegateItem) delegateItem.destroy()

    property string title
    property alias color: back.color

    property font font
    property color textColor: "#333"

    function init(opened) {
        if(scene.inited)
            return

        scene.opened = opened
        scene.inited = true
    }

    Item {
        id: scene
        width: opened? parent.width : 0
        height: parent.height
        clip: true
        visible: width > 0

        property bool opened: false
        property bool inited: false

        onOpenedChanged: initDelegate()
        onInitedChanged: initDelegate()

        function initDelegate() {
            if(!delegate)
                return
            if(delegateItem)
                return
            if(!opened)
                return

            delegateItem = delegate.createObject(back)
        }

        Behavior on width {
            NumberAnimation { easing.type: Easing.OutBack; duration: scene.inited? 300 : 0 }
        }

        Rectangle {
            id: back
            width: base.width
            height: base.height
        }
    }

    function openFromLeft() {
        scene.anchors.right = undefined
        scene.anchors.left = base.left
        back.anchors.right = undefined
        back.anchors.left = scene.left
        scene.opened = true
    }

    function openFromRight() {
        scene.anchors.right = base.right
        scene.anchors.left = undefined
        back.anchors.right = scene.right
        back.anchors.left = undefined
        scene.opened = true
    }

    function closeToLeft() {
        scene.anchors.right = undefined
        scene.anchors.left = base.left
        back.anchors.right = undefined
        back.anchors.left = scene.left
        scene.opened = false
    }

    function closeToRight() {
        scene.anchors.right = base.right
        scene.anchors.left = undefined
        back.anchors.right = scene.right
        back.anchors.left = undefined
        scene.opened = false
    }
}
