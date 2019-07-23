/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.9
import AsemanQml.Base 2.0

Item {
    id: cf_listv
    width: 100
    height: 62
    clip: true

    property alias titleBarHeight: titlebar.height
    property color titleBarDefaultColor: masterPalette.highlight
    property color titleBarDefaultTextColor: "#ffffff"
    property alias titleBarFont: title_txt.font
    property alias titleBarColor: titlebar.color

    property real headersHeight: 50*Devices.density
    property real topMargin: 30*Devices.density
    property real bottomMargin: 0
    property real headerColorDomain: 10*Devices.density
    property real headerColorHeight: 50*Devices.density

    property alias verticalVelocity: listv.verticalVelocity
    property alias horizontalVelocity: listv.horizontalVelocity

    property alias contentY: listv.contentY
    property alias originY: listv.originY

    property alias model: listv.model
    property alias footer: listv.footer

    property alias count: listv.count
    property alias atBegin: listv.atYBeginning
    property alias atEnd: listv.atYEnd

    property alias listScale: listv.scale
    property alias listTransformOrigin: listv.transformOrigin

    property Component delegate
    property Component header
    property Component customHeader

    onCustomHeaderChanged: custom_titlebar_frame.item = customHeader.createObject(custom_titlebar_frame)

    AsemanListView {
        id: listv
        anchors.top: custom_titlebar_frame.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        maximumFlickVelocity: View.flickVelocity
        clip: true

        property color color0
        property color color1

        onContentYChanged: refresh()
        onWidthChanged: refresh()

        function refresh() {
            var header_extra_area = 100*Devices.density

            var item = listv.itemAt(width/2,contentY+headerColorDomain+1+header_extra_area)
            if( !item ) {
                titlebar.color = titleBarDefaultColor
                title_txt_frame.y = titleBarHeight
                title_txt_frame.opacity = 0
                return
            }
            if( !item.itemIsHeader ) {
                return
            }

            var currentItemIndex = item.itemIndex

            var prevItem
            for( var i=currentItemIndex-1; i>=0; i-- )
                if( listv.model.get(i).isHeader ) {
                    prevItem = listv.model.get(i)
                    break
                }

            var crntItem
            for( var i=currentItemIndex; i<model.count; i++ )
                if( listv.model.get(i).isHeader ) {
                    crntItem = listv.model.get(i)
                    break
                }

            color0 = prevItem? prevItem.color : titleBarDefaultColor
            color1 = crntItem? crntItem.color : titleBarDefaultColor

            var itemY = item.y - contentY - headerColorDomain

            var itemY_ratio = (itemY + headerColorHeight)/headerColorHeight
            if( itemY_ratio < 0 )
                itemY_ratio = 0
            if( itemY_ratio > 1 )
                itemY_ratio = 1

            var red = color0.r*itemY_ratio + color1.r*(1-itemY_ratio)
            var grn = color0.g*itemY_ratio + color1.g*(1-itemY_ratio)
            var blu = color0.b*itemY_ratio + color1.b*(1-itemY_ratio)

            titlebar.color = Qt.rgba(red, grn, blu, 1)

            var title_new_y = titlebar.height + custom_titlebar_frame.height + item.y-contentY
            var title_new_opacity = (title_new_y-headerColorHeight)/header_extra_area

            var title_new_txt = crntItem.title
            if( title_new_y < titlebar.height + custom_titlebar_frame.height - title_txt_frame.height ) {
                title_new_y = titlebar.height + custom_titlebar_frame.height - title_txt_frame.height
            }
            else
            if( title_new_y > headerColorHeight ) {
                title_new_y = titlebar.height + custom_titlebar_frame.height - title_txt_frame.height
                if( prevItem )
                    title_new_txt = prevItem.title
                else
                    title_new_opacity = 0
            }

            if( title_new_opacity < 0 )
                title_new_opacity = 1

            title_txt_frame.y = title_new_y
            title_txt_frame.width = item.width
            title_txt_frame.opacity = title_new_opacity
            title_txt.text = title_new_txt
        }

        header: Item {
            id: header_item
            height: headerObj? headerObj.height + topMargin : topMargin
            width: headerObj? headerObj.width : 20

            property variant headerObj

            Component.onCompleted: {
                if( !cf_listv.header )
                    return

                headerObj = cf_listv.header.createObject(header_item)
            }
        }

        footer: Item {
            width: 20
            height: cf_listv.bottomMargin
        }

        delegate: Item {
            id: item
            width: listv.width
            height: itemObj? itemObj.height + itemIsHeader*headersHeight : headersHeight
            x: itemObj? itemObj.x : 0

            property int itemIndex: index
            property variant itemObj
            property color itemColor: color? color : "#333333"
            property string itemTitle: title
            property bool itemIsHeader: isHeader

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                color: item.itemColor
                height: headersHeight*itemIsHeader
                visible: itemIsHeader

                Text {
                    anchors.centerIn: parent
                    color: titleBarDefaultTextColor
                    font: titleBarFont
                    text: title
                }
            }

            Component.onCompleted: {
                itemObj = cf_listv.delegate.createObject(item, {"y": headersHeight*itemIsHeader, "modelItem": modelItem})
            }
        }
    }

    ScrollBar {
        scrollArea: listv; height: listv.height; width: 6*Devices.density
        anchors.right: listv.right; anchors.top: listv.top; color: titleBarColor
    }

    Rectangle {
        id: titlebar
        height: 70*Devices.density
        width: listv.width
        color: titleBarDefaultColor
        clip: true

        MouseArea {
            anchors.fill: parent
        }

        Behavior on color {
            ColorAnimation{ easing.type: Easing.OutCubic; duration: 400 }
        }

        Item {
            id: title_txt_frame
            height: headersHeight
            y: titlebar.height + custom_titlebar_frame.height

            Text {
                id: title_txt
                anchors.centerIn: parent
                color: titleBarDefaultTextColor
                font.family: AsemanApp.globalFont.family
            }
        }
    }

    Item {
        id: custom_titlebar_frame
        anchors.top: titlebar.bottom
        width: listv.width
        height: item? item.height : 0

        property variant item
        property variant itemTmp
        onItemChanged: {
            if(itemTmp)
                itemTmp.destroy()
            itemTmp = item
        }
    }

    function positionViewAtBeginning() {
        listv.positionViewAtBeginning()
    }
}
