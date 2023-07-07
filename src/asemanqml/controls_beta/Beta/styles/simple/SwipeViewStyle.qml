import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import AsemanQml.Controls.Beta 3.0

AbstractStyle {
    id: dis

    Connections {
        target: control
        function onCurrentIndexChanged() {
            listv.currentIndex = control.currentIndex;
        }
    }

    ListView {
        id: listv
        anchors.fill: parent
        orientation: ListView.Horizontal
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 200
        snapMode: ListView.SnapOneItem
        currentIndex: control.currentIndex
        onCurrentIndexChanged: if (moving) control.currentIndex = currentIndex;
        interactive: control.interactive
        clip: true
        model: {
            var res = new Array;
            for (var i=0 ;i<control.list.length; i++) {
                var item = control.list[i];
                if (item.transformOrigin == undefined)
                    continue;

                res[res.length] = item;
            }
            return res;
        }
        delegate: Control {
            id: item
            width: listv.width
            height: listv.height
            clip: true
            focusableUsingKeyboard: false


            property Item backupParent
            Component.onCompleted: {
                backupParent = modelData.parent;
                modelData.parent = item;
                modelData.anchors.fill = item;
            }
            Component.onDestruction: modelData.parent = backupParent
        }
    }
}
