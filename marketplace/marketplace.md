# Qt Aseman
<img src="https://aseman.io/projects/qtaseman/aseman-qt.png" align="left" />

## What is QtAseman

QtAseman is a set of tools, design patterns and architectures that we have developed over the years in various projects for wide range of uses. Now, with it's proven stability, we have decided to release this collection with the name QtAseman as an Open Source and Free tool under the LGPLv3 license.

![Snapshot](https://aseman.io/projects/qtaseman/snapshot.png)

It works on Linux, OSX, Windows, Android and iOS and depended only on Qt.

One of the main assets of QtAseman is that you can add it to your project without any extra change to the standard structure of the default QML app.

There are many modules and components in QtAseman that will help you create applications without use of any extra C++ code.
Also QtAseman offers a great software architecture for each module that makes development much more easier and faster.

[MORE INFORMATION](https://github.com/Aseman-Land/QtAseman)

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

## How to Install

Currently binary packages only available on the ubuntu (launchpad) repositories. To install it on the ubuntu 20.04 LTS:QAseman Core modules

Some models and abstract models with better experiance

Encrypt algorithms tools

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