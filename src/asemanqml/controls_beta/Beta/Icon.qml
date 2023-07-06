import QtQuick 2.15
import AsemanQml.Controls.Beta 3.0

Text {
    id: dis

    property string styleFileName: "IconStyle.qml"

    font.family: styledItem.styleItem.font.family
    font.pixelSize: styledItem.styleItem.font.pixelSize
    leftPadding: styledItem.styleItem.padding.left
    rightPadding: styledItem.styleItem.padding.right
    topPadding: styledItem.styleItem.padding.top
    bottomPadding: styledItem.styleItem.padding.bottom
    lineHeight: styledItem.styleItem.extra.lineHeight
    lineHeightMode: styledItem.styleItem.extra.lineHeightMode

    StyledItem {
        id: styledItem
        styleFileName: dis.styleFileName
        sourceItem: dis
    }
}
