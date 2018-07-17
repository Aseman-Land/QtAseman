import QtQuick 2.0
import AsemanQml.Base 2.0

Item {
    id: cpbar
    width: 64
    height: width

    property real lineWidth: 4*Devices.density
    property alias running: anim.running
    property real progress: 0
    property color color: "#0d80ec"
    property alias progressText: progress_text.visible

    onLineWidthChanged: itttm.refresh()
    onProgressChanged: itttm.refresh()
    onColorChanged: itttm.refresh()

    Text {
        id: progress_text
        anchors.centerIn: parent
        font.family: AsemanApp.globalFont
        font.pixelSize: 10*Devices.fontDensity
        color: cpbar.color
        text: {
            var res = Math.floor(cpbar.progress*1000)
            res = res/10
            if(res == Math.floor(res))
                res += ".0"
            return Tools.translateNumbers(res + "%")
        }
    }

    Item {
        id: itttm
        anchors.fill: parent
        anchors.centerIn: parent

        NumberAnimation {
            id: anim
            easing.type: Easing.Linear
            duration: 1500
            from: 0
            to: 360
            running: cpbar.progress != 0
            target: itttm
            properties: "rotation"
            loops: Animation.Infinite
        }

        Canvas {
            id: canvas
            anchors.fill: parent
            antialiasing: true
            renderStrategy: Canvas.Threaded
            renderTarget: Canvas.FramebufferObject
            onPaint: {
                var ctx = getContext("2d");
                ctx.strokeStyle = cpbar.color
                ctx.lineWidth = lineWidth

                var w = width
                var h = height
                var r = (Math.min(width, height) - ctx.lineWidth)/2
                var angle = Math.PI*2 * cpbar.progress

                ctx.clearRect(0, 0, w, h)
                ctx.resetTransform()
                ctx.beginPath()
                ctx.arc(w/2, h/2, r, 0, angle, false)
                ctx.stroke()
            }
        }

        function refresh() {
            canvas.requestPaint()
        }
    }
}
