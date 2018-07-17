import AsemanTools 1.1
import QtQuick 2.7
import "."

AsemanApplication {
    id: app
    applicationName: "TrApp"
    applicationAbout: "Translation App"
    applicationDisplayName: "Translation App"
    applicationVersion: "v0.0.1"
    applicationId: "e7c2f1f3-dc2a-4ec2-9268-a863a76df9c3"
    organizationDomain: "aseman.co"
    organizationName: "Aseman Team"
    source: "mainforms/MainWindow.qml"
    
    Settings {
        id: settings
        source: AsemanApp.homePath + "/settings.ini"
        category: "General"

        property string localeName: "fa"
    }

    TranslationManager {
        id: translationManager
        sourceDirectory: "translations"
        delimiters: "-"
        fileName: "lang"
        localeName: settings.localeName

        function refreshLayouts() {
            console.debug(translations)
            View.layoutDirection = textDirection
            if(localeName == "fa")
                CalendarConv.calendar = 1
            else
                CalendarConv.calendar = 0
        }
        Component.onCompleted: refreshLayouts()
        onLocaleNameChanged: refreshLayouts()
    }
}
