import QtQuick 2.15
import AsemanQml.Base 2.0
import AsemanQml.Controls.Beta 3.0

TextInput {
    id: dis
    persistentSelection: true

    property string styleFileName: "TextFieldStyle.qml"

    font: styledItem.styleItem.font
    leftPadding: styledItem.styleItem.padding.left
    rightPadding: styledItem.styleItem.padding.right
    topPadding: styledItem.styleItem.padding.top
    bottomPadding: styledItem.styleItem.padding.bottom
    clip: true
    height: styledItem.implicitHeight
    Layout.preferredHeight: styledItem.implicitHeight

    selectedTextColor: dis.Style.accentTextColor
    selectionColor: dis.Style.accentColor
    selectByMouse: Devices.isDesktop
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
