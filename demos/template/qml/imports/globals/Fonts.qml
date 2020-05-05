pragma Singleton

import QtQuick 2.10
import AsemanQml.Base 2.0

AsemanObject
{
    property alias ubuntuFont: ubuntu_font.name

    FontLoader { id: ubuntu_font; source: "fonts/Ubuntu-R.ttf" }

    function init() {
    }
}
