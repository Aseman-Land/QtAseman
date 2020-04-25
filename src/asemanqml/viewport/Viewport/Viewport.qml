import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

ViewportCore {
    id: viewportCore

    property bool androidStyle: Devices.isAndroid
    property Item mainItem
    property alias count: list.count

    onMainItemChanged: {
        if (!mainItem)
            return;

        mainItem.parent = scene;
    }

    ListObject { id: list }

    Item {
        id: scene
        anchors.fill: parent
        clip: true
    }

    function append(component, properties, type) {
        var cmp = getComponent(type);
        if (!cmp) {
            console.debug("There is no \"" + type + "\" viewportType. Available types are ", keys)
            return null
        }

        var comObj;
        if ((cmp + "").length && cmp.status === undefined) {
            comObj = createComponent(Qt.resolvedUrl(cmp));
        } else {
            comObj = cmp
        }
        if (comObj.status === Component.Error) {
            console.debug(comObj.errorString().trim())
            return null
        }

        var lastItem = (list.count? list.last() : mainItem );
        var typeObj = comObj.createObject(scene, {"list": list});
        typeObj.open = true;
        typeObj.index = Qt.binding( function() { return list.count? list.indexOf(typeObj) + 1 : 0 } )
        typeObj.count = Qt.binding( function() { return list.count } )
        typeObj.ratioChanged.connect( function(){
            if (typeObj.open || typeObj.ratio > 0)
                return;

            lastItem.parent = scene;
            list.removeAll(typeObj);
        });

        lastItem.parent = typeObj.backgroundScene;

        if ((component + "").length && component.status === undefined) {
            component = createComponent(Qt.resolvedUrl(component));
        }
        if (component.status === Component.Error) {
            console.debug(component.errorString().trim())
            return null
        }

        var obj = properties? component.createObject(typeObj.foregroundScene, properties) : component.createObject(typeObj.foregroundScene);
        if (typeObj.fillForeground)
            obj.anchors.fill = obj.parent

        list.append(typeObj);

        typeObj.foregroundItem = obj
        typeObj.backgroundItem = lastItem
        typeObj.viewport = viewportCore
        return obj
    }

    function closeLast() {
        if (list.count === 0)
            return;

        list.last().open = false;
    }
}
