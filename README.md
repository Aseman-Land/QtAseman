<img src="icons/logo.png" align="right" />

# Qt Aseman

## What is QtAseman

QtAseman is a set of tools, design patterns and architectures that we have developed over the years in various projects for wide range of uses. Now, with it's proven stability, we have decided to release this collection with the name QtAseman as an Open Source and Free tool under the LGPLv3 license.

![Snapshot](https://aseman.io/projects/qtaseman/snapshot.png)

Some main features to use on QML are:

- Viewport tools that provides unique page manager system (page, popup, stack, dialog and ...)
- Gestures for viewports 
- Transparent statusbar and optional navigation bar on mobile devices
- Some extra Qml controls components like Drawer, Header, TextField, CircularProgressBar and ...
- BackHandler system
- Font awesome and Material icons fonts
- VideoPlayer component
- Some graphical components like shadows for easy to use and better experiance
- Network and Http Request handler
- Models and Abstract models with better experience
- Encrypt/Decrypt tools
- Qt/C++ Like Hash, Map and List objects
- Tools to get more device infos like deviceId, density, keyboard height, statusBar height and ...
- Translation manager tools
- Settings manager
- Some other tools like file read/write methods, type convert methods and ...
- Process executer tools from QML

## QtAseman 3.1.x Roadmap

- iOS plugin for QtQuickControls
- Viewport's context menu type
- AsemanQml.Database module
- QtCreator wizards to create Aseman Apps easily

## How to Install

Currently binary packages only available on the ubuntu (launchpad) repositories. To install it on the ubuntu 20.04 LTS:

```bash
sudo add-apt-repository ppa:aseman/qt-modules
sudo apt install qt5aseman
```

and to install development files install `qt5aseman-dev` package.

## How to build

QtAseman uses standard Qt module mechanisms and it only depends on Qt libraries. Therefor it's quite easy to build on all platforms. Just clone it and build it easily:

```bash
git clone https://github.com/Aseman-Land/QtAseman.git
cd QtAseman
mkdir build && cd build
qmake -r ..
make -j2
make install
```

The easiest way to build is to open it using QtCreator and click on the build icon :)
Afterwards just run `make install` command to install it in the Qt location.

## How to create a QML application using QtAseman

One of the main assets of QtAseman is that you can add it to your project without any extra change to the standard structure of the default QML app.

So To create an application using QtAseman, Just create a new QML project in your QtCreator and add AsemanQML module to the project. Now you can use all QtAseman components:

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

If you wish to change any application attribute like applicationName or applicationOrganization you can create an `AsemanApp` object in the parent of  `AsemanWindow`. Although it's completely optional and you can ignore it.

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

We suggest you to also create an AsemanApplication object, because QtAseman handles config file paths better while this attributes is set.

**Note**: In order to make all modules work correctly on android devices you must replace `io.aseman.android.AsemanApplication` and `io.aseman.android.AsemanActivity` with Qt's values in the android manifest file.

## QtAseman QML Modules

There are many modules and components in QtAseman that will help you create applications without use of any extra C++ code.
Also QtAseman offers a great software architecture for each module that makes development much more easier and faster.

### AsemanQml.Base

AsemanQml.Base module provides many base and core modules for your application. For example modules like Device infos, Desktop functions tools, data type converters, lists, hashes and etc. are placed in Base module.

here is one of the main uses of Base module:

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

QtAseman makes mobile status bars transparent by default and `Devices.statusBarHeight` returns the status bar height of the device. The above example makes the status bar color blue. If there is no status bar on the device (like desktop operation systems) it returns zero as the result.

You can get other useful values like screen density, suggested font density, main OS folder locations, platform details, device type and etc. using `Devices` component.

Also there is `Tools` component that provides some extra tools for applications, like methods to read or write to/from files or methods to convert json to variant map or convert url to local path and etc.

For example below codes create sha256 hash:

```js
var sha = Tools.hash("12345", Tools.Sha256);
```

Or below codes read text from file:

```js
var text = Tools.readText("/home/bardia/file.txt");
```

There is also a `Process` component that runs processes or a great back handler component named `BackHandler`.

#### BackHandler

`BackHandler` component provides back mechanism for your application. It's simple and easy to work with, plus all components of QtAseman support it by default, therefore it handles back actions automatically without the direct interference of developer.

Below example shows you how to use `BackHandler` component in your code:

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

Beside clicking on the hide button to trigger back function, you can press Esc button or the physical back button of device. On mobile devices if there is no back function in the BackHandler stack and back() method is called, application will try to quit.

**Note**: You must use AsemanWindow object to make Esc or Physical back button work.

#### AsemanListModel

AsemanListModel provides a model component for advanced usage of QML. Below example shows how to use AsemanListModel in your code:

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

And You can manage your model using below methods:

```js
var value = model.get(idx, "propertyName");
var allValues = model.get(idx); // allValues.propertyName is equal to value
model.clear();
model.append({"name", "bardia", "age": 30});
var data = model.data; // Get all data of the model as list
var json = Tools.variantToJson(data); // Convert data to json string
```

#### Settings

Creates a settings file in a specific path and stores settings values there:

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

Every change in setting's property is saved and can be restored within the next load of application.

#### Translations

`Translations` and `TranslationManager` provide functions and tools to manage translation in your application:

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

It renders every included child item as rounded. For example below code shows an image with rounded corners:

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

`DelegateSwitch` provides a component to switch between two or more children components on the fly. For example:

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

This example shows red rectangles on even indexes and blue squeres on odd indexes.

#### ReadMore

 To read more about Base module, please read [this document](documents/AsemanQml.Base.md).

### AsemanQml.Controls

Controls module provides any control module like QtQuick.Controls. For example It provides `AsemanApplication ` , `AsemanWindow`, `SideMenu`, `Header` and many other components.

Below example shows a simple usage of the `Controls` component.

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

    Drawer {
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

Viewport module provides a new design architecture for applications. 

There is a `Viewport` component that provides a manage mechanism for your page, popup, dialogs and etc.

[![Viewport Video](https://aseman.io/aseman/viewport.jpg)](https://youtu.be/hqBt8GOXQB0ase)

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

There is also an attached property, you can use to call append function in the Viewport's childeren components:

```js
Viewport.viewport.append(...)
```

#### ViewportController

Using `ViewportController` components you won't need to create a complicated architecture. It helps you to make your architecture quite easy and dynamic.

Below example shows you how to create UI and open them easily in the apps.

Using this design architecture, you create separated UI files, link them to their specific path and just call them using controllers anywhere in the App.
`ViewportController` opens them automatically in the `Viewport`.

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
        sourceComponent: hiComponent
        viewportType: "popup" 
    }

    ViewportControllerRoute {
        route: /about:\/\/aseman\/.*/
        // You can also use `source` property and pass component's url to it.
        sourceComponent: aboutComponent
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

There is also an attached property, you can use to call trigger function in the Viewport's childeren components:

```js
MouseArea {
    onClicked: Viewport.controller.trigger("about://aseman/test", {"text": "about"})
}
```

`Viewport.controller` method returns first controller of the parent Viewport. If you wish to get all controllers as array, use `Viewport.allController` method instead.

#### ViewportType Attached Property

Using `ViewportType` attached property, you can change some attributes on the current Viewport's type item:

```js
ViewportType.gestureWidth: 10 // Change touch/mouse gesture area's width
ViewportType.touchToClose: false // Disable touch background to close feature
ViewportType.blockBack: true // Disable press back to close feature
```

### AsemanQml.Network

Network module provides components to send network requests. For Example `NetworkRequestManager` and `NetworkRequest` could send http requests like post, get, put and etc.
Below example shows you a simple usage of network module.

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

You can create many simple request files in your project and every time you need them, just send them to the server using NetworkRequestManager and get your response.

### AsemanQml.MaterialIcons and AsemanQml.Awesome

These two modules provide access to the MaterialIcons and FontAwesome font icons. The usage is easy:

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

## Advanced options using C++

If you need to access advanced options or create components inherited from QtAseman or even have further use using C++  simply add below line to your `.pro` file and use components there:

```
QT += asemancore asemangui asemanqml asemannetwork asemanwidgets asemangeo
```

## Documents

We have started to document all modules and their essential details using Doxygen standards we will put them in documents folder, but the full documentation process is under developing and not completed yet.
