import QtQuick 2.12
import AsemanQml.Viewport 2.0
import forms 1.0

WaitDialog {
    ViewportType.touchToClose: false
    ViewportType.blockBack: true

    function close() {
        ViewportType.open = false
    }
}
