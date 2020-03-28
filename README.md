<img src="icons/logo.png" align="right" />

# QtAseman

[TOC]

## What is QtAseman

QtAseman is a set of tools, design patterns and architectures that we have developed over the years in various projects, and after much usages and stability, we released them as a collection under this name as a Open Source and Free tools under the LGPLv3 license.

## How to build

QtAseman uses standard Qt modules mechanism and only depended on the Qt libraries. So it's very easy to build it on all platforms. Just clone it and build it easily:

```bash
git clone https://github.com/Aseman-Land/QtAseman.git
cd QtAseman
mkdir build && cd build
qmake -r ..
make -j2
make install
```

Easiest way is to open it on the QtCreator and click on the build icon :)
After it just run `make install` command to install it on the Qt location.

## How to create QML application using QtAseman

One of the main goal of the QtAseman, is that you adding it to your projects without any extra change to the standard structure of the default QML apps.

So To create application using QtAseman, Just create new QML project in the QtCreator and add AsemanQML module to the projects. After it you can use all QtAseman components:

```js
import AsemanQml.Controls 2.0
import QtQuick.Controls 2.12

AsemanWindow {
    visible: true
    width: 480
    height: 720
    title: qsTr("QtAseman Example")
    
    Label {
        anchors.centerIn: parent
        text: "Hello World! :)"
    }
}
```

If you wish to change application attributes like applicationName and applicationOrganization you can create a `AsemanApp` object in the parent of the `AsemanWindow`. It's completely optional and you can ignore it.

```js
import AsemanQml.Controls 2.0

AsemanApplication {
    id: app
    applicationAbout: "QtAseman Application"
    applicationDisplayName: "QtAseman"
    applicationId: "be2a1f0c-34aa-44ed-8e65-4b1720e560b8"
    organizationDomain: "aseman.io"
    
    AsemanWindow {
        visible: true
        width: 480
        height: 720
    }
}
```

We suggest you to also create AsemanApplication object, Because QtAseman handle config file paths in the right and better place when you set this attributes.

**Note**: On the android devices to works all modules correctly you must replace `io.aseman.android.AsemanApplication` and `io.aseman.android.AsemanActivity` with Qt's values on the android manifest file.

## QtAseman QML Modules

There are many modules and components in the QtAseman that help you create application without any extra C++ code in your applications.
Also QtAseman suggest a great Software Architecture for every use of the modules that make development easiest and quicker.

### AsemanQml.Base

Base module provides many base and core modules for your application. For example modules like Device infos, Desktop functions tools, data type converters, lists, hashes and ... placed in the Base module.

this is on of the Main use of the Base module:

```js
import AsemanQml.Controls 2.0
import AsemanQml.Base 2.0

AsemanWindow {
    visible: true
    width: 480
    height: 720
    title: qsTr("QtAseman Example")
    
    Rectangle {
        height: Devices.statusBarHeight
        width: parent.width
        color: "blue"
    }
}
```

QtAseman make mobile status bars transparent by default and `Devices.statusBarHeight` return status bar height of the device. So above example make status bar color blue. If there is no status bar on the device (like desktop operation systems) it returns zero as the result.

You can get many other values like screen density, suggested font density, main OS folder locations, platform details, device type and ... using `Devices` component.

Also there is `Tools` component that provides some extra tools for the application like methods to read or write to/from files. Or method to convert json to variant map or convert url to local path and ...

for example below codes create sha256 hash:

```js
var sha = Tools.hash("12345", Tools.Sha256);
```

or below codes read text from file:

```js
var text = Tools.readText("/home/bardia/file.txt");
```

There is also a `Process` component that run processes or a great back handler component which name is `BackHandler`.

#### BackHandler

`BackHandler` component provides back mechanism to your application. It's simple and easy to work and also all components of the QtAseman supports it by default. So It's works in the background many time and you don't need to use it.

Below example show you how to use `BackHandler` component in your code:

```js

Button {
    anchors.centerIn: parent
    text: "Show"
    onClicked: subRect.visible = true
}

Rectangle {
    id: subRect
    anchors.fill: parent
    visible: false
    onVisibleChanged: {
        if (visible)
            BackHandler.pushHandler(subRect, function(){ subRect.visible = false })
        else
            BackHandler.removeHandler(subRect)
    }

    Button {
        anchors.centerIn: parent
        text: "Hide"
        onClicked: BackHandler.back()
    }
}
```

Except of the clicking on the Hide button, You can press Esc button or Physical device back button, to active back function. On the mobile devices if there is no back function in the BackHandler stack and back() method called, application try to quit.

**Note**: You must use AsemanWindow object to make Esc or Physical back button works.

#### AsemanListModel

AsemanListModel provide a model component for advance usage on the QML. Below example show how to use AsemanListModel in your code:

```js
AsemanListModel {
    id: model
    data: [
        {
            "name": "bardia",
            "age": 30 + 2 // It supports js values too.
        },
        {
            "name": "amir",
            "age": 31
        }
    ]
    // cachePath store model data to the file and restore it everytime
    // Application load again
    cachePath: AsemanApp.homePath + "/ages.model"
}
```

**Note**: `AsemanApp.homePath` returns standard path to store config files.

and You can manage your model using below methods:

```js
var value = model.get(idx, "propertyName");
var allValues = model.get(idx); // allValues.propertyName is equal to value
model.clear();
model.append({"name", "bardia", "age": 30});
var data = model.data; // Get all data of the model as list
var json = Tools.variantToJson(data); // Convert data to json string
```

#### Settings

Creates a settings file on the special path and store settings there:

````js
Settings {
    id: settings
    category: "General"
    source: AsemanApp.homePath + "/ui-settings.ini"

    property bool languageInited: false
    property int nightMode: 0
    property int colorTheme: 0
    property int darkColorTheme: 3
}
````

Every changes on the setting's property, saved and restore on the next application load.

#### Translations

`Translations` and `TranslationManager` provides functions and tools to manager translations on your applications:

```js
TranslationManager {
    id: translationManager
    
    // Finds all lang-*.qm files in the sourceDirectory using three below lines
    sourceDirectory: "../translations"
    delimiters: "-"
    fileName: "lang"
    
    localeName: "fa"
}

Button {
    // Everytime translation changed to other language, Every refresher texts
    // will refreshed and translated to the new language
    text: qsTr("Dismiss") + Translations.refresher
}
```

#### RoundedItem

It render every included child item, rounded. For example below code show an image with rounded corners:

```js
RoundedItem {
    width: 100
    height: 100
    radius: 10
    
    Image {
        anchors.fill: parent
        source: "image.png"
    }
}
```

#### DelegateSwitch

`DelegateSwitch` provide component to switch between two or more child components on the fly. for example:

```js
ListView {
    model: 20
    delegate: DelegateSwitch {
        current: model.index % 2
        Component {
            Rectangle {
                width: 100; height: 40
                color: "red"
            }
        }
        Component {
            Rectangle {
                width: 40; height: 40
                color: "blue"
            }
        }
    }
}
```

This example above show a red rectangle on the even indexes and a blue squere on the odd indexes.

#### ReadMore

 To read more about Base module, please read [this document](documents/AsemanQml.Base.md).

### AsemanQml.Controls

Controls module provide every controls modules like QtQuick.Controls. For example It provide `AsemanApplication ` , `AsemanWindow`, `SideMenu`, `Header` and many other Component.

Below example show a simple usage of the `Controls` components.

```js
import QtQuick 2.9
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0

AsemanWindow {
    visible: true
    width: 480
    height: 720
    title: qsTr("Hello World")
    
    Header {
        width: parent.width
        text: "Hello"
        color: "#18f"
    }

    SideMenu {
        id: menu
        anchors.fill: parent
        delegate: Rectangle {
            anchors.fill: parent
            color: "#333"
        }
    }

    HeaderMenuButton {
        id: btn
        /* 
         * If BackHandler stack is not empty, It shows back 
         * button instead of hamburger btn. 
         */
        ratio: BackHandler.count? 1 : menu.percent
        onClicked: BackHandler.count? BackHandler.back() : menu.show()
    }
}
```

### AsemanQml.Viewport

Viewport module provide new design architecture for applications. 

There is a `Viewport` component that provides you page, popup, dialogs and ... manager mechanism.
Below example shows you the usage of the `Viewport` component.

```js
import AsemanQml.Viewport 2.0
/*
 * Viewport component manage pages and Way of the they opened.
 * Like popups, pages, dialogs or ...
 * It also supports BackHandler by default like other QtAseman components
 */
Viewport {
    id: viewPort
    anchors.fill: parent
    mainItem: Page {
        // Main/Default Viewport item
        anchors.fill: parent

        Button {
            text: "Open"
            anchors.centerIn: parent
            
            // append hiComponent to the viewPort stack and open it as page
            // append() returns a refrence to the created ui object.
            // Types are: page, activity, popup, dialog and drawer
            onClicked: viewPort.append(hiComponent, undefined, "page")
        }
    }
}

Component {
    id: hiComponent
    Page {
        id: page
        anchors.fill: parent
        property int cnt

        Button {
            id: btn
            text: "Open " + (page.cnt+1)
            anchors.centerIn: parent
            
            // append method could also pass properties to the dest object
            onClicked: viewPort.append(hiComponent, {"counter": page.cnt+1}, "popup")
        }
    }
}
```

#### ViewportController

Using `ViewportController` components you don't need to create complicated architecture. It make your architecture easy and dynamic.

Below example show you how to create UI and open them easily in the apps.

Using this design architecture, You creates UI files separated, Link them to their special paths and just call them using controller from anywhere of the App.
`ViewportController` open them automatically in the `Viewport`.

```js
Viewport {
    id: viewPort
    anchors.fill: parent
    mainItem: Page {
        anchors.fill: parent

        Button {
            text: "Open"
            anchors.centerIn: parent
            // Trigger the path and open UI item that linked to the path.
            // trigger() returns a refrence to the created ui object.
            onClicked: controller.trigger("main://test/bardia")
        }
    }
}

ViewportController {
    id: controller
    viewport: viewPort

    // Define all your UI routes that connect paths to UI components.
    ViewportControllerRoute {
        route: /main:\/\/test\/.*/
        component: hiComponent
        viewportType: "popup" 
    }

    ViewportControllerRoute {
        route: /about:\/\/aseman\/.*/
        // You can also set component's file path to the component property.
        component: aboutComponent
        viewportType: "page" 
    }
}

Component {
    id: hiComponent
    Page {
        anchors.fill: parent
        
        Button {
            text: "About"
            anchors.centerIn: parent
            /*
             * You can also pass properties to object using js map
             * or using html query way (about://aseman/test?text=about&color=blue)
             */
            onClicked: controller.trigger("about://aseman/test", {"text": "about"})
        }
    }
}
Component {
    id: aboutComponent
    Label {
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        
         // If you specify a url property, triggered url will put to this property
        property string url
    }
}
```

### AsemanQml.Network

Network module provides components to send network requests. for Example `NetworkRequestManager` and `NetworkRequest` could send http requests like post, get, put and ....
Below example shows you a simple usage of the network modules.

```js
import AsemanQml.Network 2.0

Button {
    text: "Signup"
    onClicked: networkManager.post(signInRequest) // get, post, put or ...
}

BusyIndicator { running: signInRequest.refreshing }

NetworkRequestManager { id: networkManager }

NetworkRequest {
    id: signInRequest
    contentType: NetworkRequest.TypeJson
    url: "https://example.com/auth/signIn"
    headers: {
        "Authorization": "Bearer ...",
    }

    // Properties will post as json file map
    property string username: "test"
    property string password: "pass1234"

    onServerError: ; // server error codes
    onClientError: ; // client error codes
    onSuccessfull: {
        // Response contains response map if it's json
        // or if not response text
        console.debug(response.token)
    }
}
```

You can create many simple request files on your project and every time you need them, just send them to the server using NetworkRequestManager and get back response.

### AsemanQml.MaterialIcons and AsemanQml.Awesome

These two modules provides access to the MaterialIcons and FontAwesome font icons. The usage is easy:

```js
import AsemanQml.MaterialIcons 2.0
import AsemanQml.Awesome 2.0

Label {
    font.family: Awesome.family
    text: Awesome.fa_github
}
Label {
    font.family: MaterialIcons.family
    text: MaterialIcons.mdi_github
}
```

## Advance Usage on the C++

If you need to advance usage and inherit from component or using them on the C++ just simply add below line to your `.pro` file and use components there:

```
QT += asemancore asemangui asemanqml asemannetwork asemanwidgets asemangeo
```

## Documents

The full documentation process is under developing and Not completed yet. But We started documenting all modules and all details using Doxygen standards and put them on documents folder.
