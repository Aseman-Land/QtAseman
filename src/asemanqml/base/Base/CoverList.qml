import QtQuick 2.4
import AsemanQml.Base 2.0

Item {
    id: coverList

    property alias model: listv.model
    property alias currentIndex: listv.currentIndex

    property real itemsWidth: 500*Devices.density
    property real itemsPadding: 8*Devices.density
    property real originY: height

    property Component delegate
    property Component internalDelegate

    ListView {
        id: listv
        anchors.fill: parent
        orientation: Qt.Horizontal
        displayMarginBeginning: 200000
        displayMarginEnd: 200000

        leftMargin: listv.width/2 - itemsWidth/2
        rightMargin: listv.width - leftMargin - listv.width/3
        snapMode: ListView.SnapToItem
        preferredHighlightBegin: width/2 - itemsWidth/2
        preferredHighlightEnd: width/2 + itemsWidth/2

        highlightRangeMode: ListView.StrictlyEnforceRange

        delegate: Item {
            id: item
            height: listv.height
            width: listv.width/3
            z: {
                if(item.itemMiddle < lisvAvWidth/2 - width/2)
                    return index
                else
                if(item.itemMiddle > lisvAvWidth/2 + width/2)
                    return listv.count - index
                else
                    return listv.count
            }
            readonly property real padX: {
                if(item.itemMiddle < lisvAvWidth/2) {
                    var leftSide = listenter.result.x - itemsPadding*index + padding
                    if(leftSide < padding)
                        return - listenter.result.x + itemsPadding*index
                    else
                        return 0
                } else {
                    var rightSide = listenter.result.x + item.width + itemsPadding * (listv.count - index - 1) + padding*2
                    if(rightSide > listv.width)
                        return listv.width - item.width - listenter.result.x - itemsPadding * (listv.count - index - 1) - padding*2
                    else
                        return 0
                }
            }

            readonly property real lisvAvWidth: listv.width - listv.count*itemsPadding
            readonly property real padding: itemsWidth/2 - width/2
            readonly property real globalX: listenter.result.x + padX
            readonly property real ratio: (globalX) / (listv.width - itemsWidth)
            readonly property real ratio2: (globalX - index*itemsPadding) / (lisvAvWidth - itemsWidth)

            readonly property real itemMiddle: listenter.result.x + item.width/2

            PointMapListener {
                id: listenter
                source: item
                dest: listv
            }

            Item {
                width: parent.width
                height: parent.height
                x: itemsWidth/2 - parent.width/2
                z: internalProxy.object? internalProxy.object.z : 0

                ProxyComponent { id: internalProxy; source: coverList.internalDelegate }
            }

            Item {
                width: itemsWidth
                height: parent.height
                x: item.padX
                z: delegateProxy.object? delegateProxy.object.z : 0
                transform: Rotation {
                    origin.x: item.ratio<0.5? 0 : itemsWidth
                    origin.y: originY
                    axis { x: 0; y: 1; z: 0 }
                    angle: 120 * (0.5 - item.ratio)
                }

                ProxyComponent { id: delegateProxy; source: coverList.delegate }
            }
        }
    }
}
