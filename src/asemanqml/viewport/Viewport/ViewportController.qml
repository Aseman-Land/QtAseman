import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

ViewportControllerCore {
    function trigger(url, properties, viewport) {
        if (properties === undefined)
            properties = {};
        if (viewport === undefined)
            viewport = null;

        var map = lookup(url, properties, viewport)
        return map.viewport.append(map.component, map.properties, map.type)
    }
}
