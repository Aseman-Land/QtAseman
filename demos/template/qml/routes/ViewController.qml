import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

ViewportController {
    id: viewController

    property int waitCount: 0
    property variant waitObj

    onWaitCountChanged: {
        if (waitCount) {
            if (!waitObj) waitObj = trigger("dialog:/wait");
        } else {
            if (waitObj) waitObj.close()
        }
    }

    ViewportControllerRoute {
        route: /dialog:\/general\/error.*/
        source: "ErrorDialog.qml"
    }

    ViewportControllerRoute {
        route: /dialog:\/wait/
        source: "WaitDialog.qml"
    }

    ViewportControllerRoute {
        route: /\w+\:\/dialog\/example.*/
        source: "ExamplePopup.qml"
    }
}

