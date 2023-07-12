import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

AbstractStyle {
    id: dis
    implicitHeight: 46

    Connections {
        target: control
        function onCurrentIndexChanged() {
            listv.currentIndex = control.currentIndex;
        }
    }

    Rectangle {
        anchors.fill: listv
        anchors.margins: 3
        anchors.leftMargin: -3
        anchors.rightMargin: -3
        radius: 10
        color: control.Style.backgroundColor
    }

    Rectangle {
        anchors.fill: listv
        anchors.margins: 3
        anchors.leftMargin: -3
        anchors.rightMargin: -3
        color: control.Style.foregroundColor
        opacity: 0.1
        radius: 10
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
            listv.width = Qt.binding(function(){ return Math.min(dis.width-18, width); });
        }

        highlight: Item {
            FastDropShadow {
                anchors.fill: back
                source: back
                horizontalOffset: 0
                verticalOffset: 1
                radius: 5
                opacity: 0.2
                color: control.Style.foregroundColor
            }

            Rectangle {
                id: back
                anchors.fill: parent
                anchors.margins: 7
                anchors.leftMargin: 1
                anchors.rightMargin: 1
                color: control.Style.backgroundColor
                radius: 8

                Rectangle {
                    anchors.fill: parent
                    color: "#fff"
                    radius: 8
                    opacity: 0.3
                }
            }
        }

        delegate: Item {
            id: item
            width: modelData.visible? modelData.width : 0
            height: listv.height
            opacity: modelData.visible? 1 : 0
            enabled: modelData.visible
            clip: true

            Connections {
                target: modelData
                function onClicked() {
                    listv.currentIndex = model.index
                }
            }

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
