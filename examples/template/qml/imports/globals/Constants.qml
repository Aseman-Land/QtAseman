pragma Singleton

import QtQuick 2.10
import AsemanQml.Base 2.0

QtObject {
    readonly property int width: 480
    readonly property int height: 800
    
    readonly property string cachePath: AsemanApp.homePath + "/cache"

    Component.onCompleted: {
        Tools.mkDir(cachePath)
    }
}
