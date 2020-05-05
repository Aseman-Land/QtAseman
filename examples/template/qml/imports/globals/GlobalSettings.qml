pragma Singleton

import QtQuick 2.7
import AsemanQml.Base 2.0

Settings {
        category: "General"
        source: AsemanApp.homePath + "/settings.ini"

        property bool languageInited: false
}

