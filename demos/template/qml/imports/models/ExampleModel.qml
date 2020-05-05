import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Models 2.0
import requests 1.0
import globals 1.0

AsemanListModel {
    cachePath: Constants.cachePath + "/example.cache"

    ExampleRequest {
        id: req
        allowGlobalBusy: true
    }

    AsemanListModelSource {
        source: req.response
    }
}
