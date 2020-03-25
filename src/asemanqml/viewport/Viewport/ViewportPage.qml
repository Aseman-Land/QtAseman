import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: rootItem

    property alias header: page.header
    property alias title: page.title

    default property alias pageData: page.data

    Page {
        id: page
        anchors.fill: parent
    }
}
