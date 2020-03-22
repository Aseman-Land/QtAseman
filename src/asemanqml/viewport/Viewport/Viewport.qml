import QtQuick 2.0
import AsemanQml.Base 2.0

Item {

    property bool androidStyle: Devices.isAndroid
    property int layoutDirection: View.layoutDirection
    property Item mainItem

    onMainItemChanged: {
        if (!mainItem)
            return;

        mainItem.parent = scene;
    }

    ListObject {
        id: list
    }

    Item {
        id: scene
        anchors.fill: parent
        clip: true
    }

    function appendCustom(component, properties, type) {
        var lastItem = (list.count? list.last() : mainItem );
        var typeObj = type.createObject(scene);
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

        var obj = properties? component.createObject(typeObj.foregroundScene, properties) : component.createObject(typeObj.foregroundScene);
        list.append(typeObj);

        typeObj.childItem = obj
        return obj
    }

    function appendPage(component, properties) { return appendCustom(component, properties, androidStyle? androidDefaultPages : iosNormal ) }
    function appendPopup(component, properties) { return appendCustom(component, properties, androidStyle? androidActivity : iosPopup ) }
    function appendDialog(component, properties) { return appendCustom(component, properties, androidStyle? androidDialog : iosDialog ) }
    function appendBottomDrawer(component, properties) { return appendCustom(component, properties, androidStyle? androidBottomDrawer : iosBottomDrawer ) }

    function closeLast() {
        if (list.count === 0)
            return;

        list.last().open = false;
    }

    property alias androidActivity: androidActivity
    property alias androidBottomDrawer: androidBottomDrawer
    property alias androidDefaultPages: androidDefaultPages
    property alias androidDialog: androidDialog

    Component { id: androidActivity; AndroidActivityViewport {} }
    Component { id: androidBottomDrawer; AndroidBottomDrawerViewport {} }
    Component { id: androidDefaultPages; AndroidDefaultPagesViewport {} }
    Component { id: androidDialog; AndroidDialogViewport {} }

    property alias iosBottomDrawer: iosBottomDrawer
    property alias iosDialog: iosDialog
    property alias iosNormal: iosNormal
    property alias iosPopup: iosPopup

    Component { id: iosBottomDrawer; IOSBottomDrawerViewport {} }
    Component { id: iosDialog; IOSDialogViewport {} }
    Component { id: iosNormal; IOSNormalViewport {} }
    Component { id: iosPopup; IOSPopupViewport {} }
}
