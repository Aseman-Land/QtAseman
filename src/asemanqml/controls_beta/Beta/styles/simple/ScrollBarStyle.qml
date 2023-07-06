import QtQuick 2.15
import AsemanQml.Controls.Beta 3.0
import "../.." as Root

AbstractStyle {
    id: dis
    implicitWidth: 8

    opacity: control.flickArea.movingVertically || control.flickArea.movingHorizontally || control.forceVisible? 1 : 0

    function position()
    {
        var ny = 0;
        if (control.orientation == Qt.Vertical)
            ny = control.flickArea.visibleArea.yPosition * dis.height;
        else
            ny = control.flickArea.visibleArea.xPosition * dis.width;
        if (ny > 2) return ny; else return 2;
    }

    function size()
    {
        var nh, ny;

        if (control.orientation == Qt.Vertical)
            nh = control.flickArea.visibleArea.heightRatio * dis.height;
        else
            nh = control.flickArea.visibleArea.widthRatio * dis.width;

        if (control.orientation == Qt.Vertical)
            ny = control.flickArea.visibleArea.yPosition * dis.height;
        else
            ny = control.flickArea.visibleArea.xPosition * dis.width;

        if (ny > 3) {
            var t;
            if (control.orientation == Qt.Vertical)
                t = Math.ceil(dis.height - 3 - ny);
            else
                t = Math.ceil(dis.width - 3 - ny);
            if (nh > t) return t; else return nh;
        } else return nh + ny;
    }

    Rectangle {
        id: bilbilak
        color: control.color
        smooth: true
        radius: width/2
        x: control.orientation == Qt.Vertical ? 2 : position()
        width: control.orientation == Qt.Vertical ? dis.width - 4 : diagonal
        y: control.orientation == Qt.Vertical ? position() : 2
        height: control.orientation == Qt.Vertical ? diagonal : dis.height - 4
        opacity: 0.5

        property real diagonal: size()<20? 20 : size()
    }

    Behavior on opacity {
        NumberAnimation { duration: 300 }
    }
}
