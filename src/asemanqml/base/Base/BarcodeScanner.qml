import QtQuick 2.0
import QtMultimedia 5.8
import QtQuick.Controls 2.2 as QtControls
import AsemanQml.Base 2.0

Item {
    id: scanner

    property alias refreshInterval: timer.interval
    property bool active: false
    property alias enabledDecoders: decoder.enabledDecoders
    property size resolution: Qt.size(640, 480)
    property bool captureMode: true

    signal tagFound(string tag)

    onActiveChanged: {
        if(active)
            timer.restart()
        else
            timer.stop()
    }

    function capture() {
        if(camera.lastFile.length)
            return false

        var path = AsemanApp.tempPath + "/barcodes"
        var fileName = "barcode" + " - " + Tools.dateToMSec(new Date)
        Tools.mkDir(path)
        if(captureMode) {
            camera.imageCapture.captureToLocation(path + "/" + fileName)
        } else {
            grabber.fileName = fileName
            grabber.save(path, Qt.size(video.width, video.height))
        }
        return true
    }

    ItemGrabber {
        id: grabber
        item: video
        suffix: "jpg"
        onSaved: camera.decodePath(dest)
    }

    Camera {
        id: camera
        captureMode: Camera.CaptureStillImage
        imageCapture {
            resolution: scanner.resolution
            onImageSaved: camera.decodePath(path)
        }

        function decodePath(path) {
            camera.lastFile = path
            decoder.decodeImageFromFile(Devices.localFilesPrePath + camera.lastFile)
        }

        property string lastFile
    }

    VideoOutput {
        id: video
        source: camera
        anchors.fill: parent
        focus : visible
    }

    QZXing {
        id: decoder
        enabledDecoders: QZXing.DecoderFormat_QR_CODE
        onTagFound: scanner.tagFound(tag)
        onDecodingFinished: {
            Tools.deleteFile(camera.lastFile)
            camera.lastFile = ""
            timer.restart()
        }
    }

    Timer {
        id: timer
        interval: 1000
        repeat: false
        onTriggered: scanner.capture()
    }
}
