import QtQuick 2.9
import AsemanQml.Controls.Beta 3.0
import AsemanQml.Controls.Beta 3.0

ScrollViewCore {
    id: dis
    styleFileName: "ScrollViewStyle.qml"
    focusableUsingKeyboard: false

    onFlickAreaChanged: {
        if (!flickArea)
            return;

        dis.data = [flickArea, styleItem];
        flickArea.anchors.fill = dis;
    }
}
