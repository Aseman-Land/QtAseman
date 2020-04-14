import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

ViewportControllerCore {
    function trigger(url, properties) {
        if (properties === undefined)
            properties = {}

        var map = lookup(url, properties)
        return map.viewport.append(map.component, map.properties, map.type)
    }
}
