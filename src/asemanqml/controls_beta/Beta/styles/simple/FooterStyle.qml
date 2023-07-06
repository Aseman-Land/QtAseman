import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import AsemanQml.Controls.Beta 3.0

AbstractStyle {
    id: dis
    implicitHeight: 60

    Connections {
        target: control
        function onCurrentIndexChanged() {
            listv.currentIndex = control.currentIndex;
        }
    }

    Rectangle {
        anchors.fill: parent
        color: control.Style.backgroundColor
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        color: control.Style.foregroundColor
        height: 1
        opacity: 0.2
    }

    ListView {
        id: listv
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        orientation: ListView.Horizontal
        snapMode: ListView.SnapToItem

        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        highlightRangeMode: ListView.ApplyRange
        highlightFollowsCurrentItem: true
        highlightMoveDuration: 200

        currentIndex: control.currentIndex
        onCurrentIndexChanged: control.currentIndex = currentIndex;

        interactive: control.interactive
        clip: true
        model: {
            var res = new Array;
            var width = 0;
            for (var i=0 ;i<control.list.length; i++) {
                var item = control.list[i];
                if (item.transformOrigin == undefined)
                    continue;

                width += item.width;
                res[res.length] = item;
            }

            listv.width = Qt.binding(function(){ return Math.min(dis.width - 12, width); });
            return res;
        }

        highlight: Item {
            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 3
                radius: height/2
                anchors.top: parent.top
                color: control.Style.accentColor
            }
        }

        delegate: Item {
            id: item
            width: modelData.width
            height: listv.height
            clip: true

            Connections {
                target: modelData
                function onClicked() {
                    listv.currentIndex = model.index
                }
            }

            Component.onCompleted: {
                modelData.parent = item;
                modelData.anchors.left = item.left;
                modelData.anchors.top = item.top;
                modelData.anchors.bottom = item.bottom;
            }
        }
    }
}
