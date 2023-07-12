import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import AsemanQml.Base 2.0

AbstractStyle {
    id: dis
    implicitHeight: Devices.navigationBarHeight + Devices.standardTitleBarHeight*1.2

    padding {
        bottom: Devices.navigationBarHeight
    }

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
        opacity: 0.1
    }

    ListView {
        id: listv
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Devices.navigationBarHeight

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
            for (var i=0 ;i<control.list.length; i++) {
                var item = control.list[i];
                if (item.transformOrigin == undefined)
                    continue;

                item.widthChanged.connect(listv.recalculateWidth);
                item.visibleChanged.connect(listv.recalculateWidth);
                res[res.length] = item;
            }

            return res;
        }

        onModelChanged: recalculateWidth()

        function recalculateWidth() {
            var width = 0;
            for (var i=0; i<listv.model.length; i++)
            {
                var item = model[i];
                if (item && item.visible)
                    width += item.width;
            }
            listv.width = Qt.binding(function(){ return Math.min(dis.width, width); });
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
            width: modelData.visible? modelData.width : 0
            height: listv.height
            opacity: modelData.visible? 1 : 0
            enabled: modelData.visible
            clip: true

            property Item backupParent
            Component.onCompleted: {
                backupParent = modelData.parent;
                modelData.parent = item;
                modelData.anchors.left = item.left;
                modelData.anchors.top = item.top;
                modelData.anchors.bottom = item.bottom;
                if (modelData.clicked != undefined)
                    modelData.clicked.connect(function(){listv.currentIndex = model.index});
            }
            Component.onDestruction: modelData.parent = backupParent
        }
    }
}
