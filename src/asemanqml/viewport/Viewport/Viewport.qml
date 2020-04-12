import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

ViewportCore {

    property bool androidStyle: Devices.isAndroid
    property int layoutDirection: View.layoutDirection
    property Item mainItem

    onMainItemChanged: {
        if (!mainItem)
            return;

        mainItem.parent = scene;
    }

    ListObject { id: list }
    HashObject { id: viewportsHash }
    HashObject { id: componentsHash }

    Item {
        id: scene
        anchors.fill: parent
        clip: true
    }

    function append(component, properties, type) {
        var cmp = getComponent(type);
        var comObj;
        if ((cmp + "").length && cmp.status == undefined) {
            if (!viewportsHash.contains(cmp)) {
                comObj = Qt.createComponent(cmp);
                viewportsHash.insert(cmp, comObj);
            } else {
                comObj = viewportsHash.value(cmp)
                if (!comObj) {
                    comObj = Qt.createComponent(cmp);
                    viewportsHash.remove(cmp);
                    viewportsHash.insert(cmp, comObj);
                }
            }
        } else {
            comObj = cmp
        }

        var lastItem = (list.count? list.last() : mainItem );
        var typeObj = comObj.createObject(scene, {"list": list});
        typeObj.layoutDirection = Qt.binding( function(){ return layoutDirection } )
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

        if ((component + "").length && component.status == undefined) {
            var key = component
            if (!componentsHash.contains(key)) {
                component = Qt.createComponent(key)
                componentsHash.insert(key, component)
            } else {
                component = componentsHash.value(key)
                if (!component) {
                    component = Qt.createComponent(key);
                    componentsHash.remove(key);
                    componentsHash.insert(key, component);
                }
            }
        }

        var obj = properties? component.createObject(typeObj.foregroundScene, properties) : component.createObject(typeObj.foregroundScene);
        list.append(typeObj);

        typeObj.foregroundItem = obj
        typeObj.backgroundItem = lastItem
        return obj
    }

    function closeLast() {
        if (list.count === 0)
            return;

        list.last().open = false;
    }
}
