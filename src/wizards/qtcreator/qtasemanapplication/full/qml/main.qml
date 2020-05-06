import QtQuick 2.12
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import globals 1.0

AsemanApplication {
    id: app
    applicationAbout: "It's %{ProjectName} app"
    applicationDisplayName: "%{ProjectName}"
    Component.onCompleted: {
        Fonts.init()

        if (Devices.isDesktop) Devices.fontScale = 1.1
        if (Devices.isAndroid) Devices.fontScale = 0.92
        if (Devices.isIOS) Devices.fontScale = 1.1
    }

    MainWindow {
        visible: true
        font.family: Fonts.ubuntuFont
    }
}
