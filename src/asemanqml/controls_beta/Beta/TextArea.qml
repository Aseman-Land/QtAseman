import QtQuick 2.15
import AsemanQml.Controls.Beta 3.0
import AsemanQml.Controls.Beta 3.0

TextEdit {
    id: dis

    property string styleFileName: "TextAreaStyle.qml"

    font: styledItem.styleItem.font
    leftPadding: styledItem.styleItem.padding.left
    rightPadding: styledItem.styleItem.padding.right
    topPadding: styledItem.styleItem.padding.top
    bottomPadding: styledItem.styleItem.padding.bottom
    clip: true
    height: Math.max(32, contentHeight + 18)

    selectedTextColor: dis.Style.accentTextColor
    selectionColor: dis.Style.accentColor
    selectByMouse: true
    color: dis.Style.foregroundColor

    property string placeholderText
    signal contextMenuRequest(real x, real y)

    Keys.onTabPressed: {
        styledItem.focusNextItem()
    }

    Control {
        id: styledItem
        styleFileName: dis.styleFileName
        sourceItem: dis
        onFocusedInUsingKeyboardChanged: {
            dis.focus = true;
            dis.forceActiveFocus();
        }
    }
}
