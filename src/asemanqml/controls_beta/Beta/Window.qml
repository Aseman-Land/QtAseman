import QtQuick 2.0
import QtQuick.Window 2.15 as QtWindow
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0
import AsemanQml.Controls.Beta 3.0

QtWindow.Window {
    id: win
    data: [viewport]

    property alias viewport: viewport
    default property alias items: scene.data

    property bool backController: true
    property bool try_close: false

    signal closeRequest()

    onCloseRequest: if(backController) AsemanApp.back()

    Style.stylesSearchPath: [":/AsemanQml/Controls/Beta/styles/"]
    Style.styleName: "simple"
    Style.primaryColor: MainPalette.background
    Style.primaryTextColor: MainPalette.foreground
    Style.accentColor: MainPalette.highlight
    Style.accentTextColor: MainPalette.highlightText
    Style.foregroundColor: MainPalette.foreground
    Style.backgroundColor: MainPalette.background
    Style.baseColor: MainPalette.base
    Style.baseTextColor: MainPalette.baseText

    Viewport {
        id: viewport
        anchors.fill: parent
        mainItem: Item {
            id: scene
            anchors.fill: parent
        }
    }

    Timer {
        id: timer_delayer
        interval: 300
        repeat: false
    }

    Connections {
        target: AsemanApp
        function onBackRequest() {
            if(timer_delayer.running)
                return

            timer_delayer.start()
            var res = BackHandler.back()
            if( !res && !Devices.isDesktop )
                win.tryClose()
        }
    }

    function tryClose() {
        try_close = true
        close()
    }

    Component.onCompleted: {
        View.registerWindow(win)
        View.root = win
    }
}
