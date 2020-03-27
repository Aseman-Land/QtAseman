# AsemanQml.Base

 ## AsemanApp

`AsemanApp` static component, provides methods, signals and properties to work with QGuiApplication and Other app functionallity.

### Request Permissions

To request or check permission (only on android) you using `requestPermissions` and `checkPermissions` methods like below example:

````js
AsemanApp.requestPermissions(["android.permission.CAMERA", 
                              "android.permission.READ_EXTERNAL_STORAGE"], 
                             function(res) {
    if (res["android.permission.CAMERA"] === true) {
        ...
    }
    if (res["android.permission.READ_EXTERNAL_STORAGE"] === true) {
        ...
    }
});
````

or

```js
var res = AsemanApp.checkPermissions(["android.permission.CAMERA"]);
if (res["android.permission.CAMERA"] === true) {
    ...
}
```

### Get application related paths

Using below properties you can get standard paths of the OS:

| Property              | Description                                            |
| :-------------------- | ------------------------------------------------------ |
| AsemanApp.homePath    | Returns path to store app configs and other files (ro) |
| AsemanApp.startPath   | Returns working directory of the app (ro)              |
| AsemanApp.appPath     | Returns application directory path (ro)                |
| AsemanApp.appFilePath | Returns application file path (ro)                     |
| AsemanApp.logPath     | Returns suggested dir path to store logs (ro)          |
| AsemanApp.confsPath   | Returns suggested dir path to store configs (ro)       |
| AsemanApp.tempPath    | Returns suggested dir path to store temp files (ro)    |
| AsemanApp.backupsPath | Returns suggested dir path to store backup files (ro)  |
| AsemanApp.cameraPath  | Returns camera dir path (ro)                           |

### Application Details

Set and Read application details like name and organization using below properties

| Property                         | Description                              |
| -------------------------------- | ---------------------------------------- |
| AsemanApp.applicationName        | Application name (rw)                    |
| AsemanApp.applicationVersion     | Version string of the application (rw)   |
| AsemanApp.organizationName       | Application organization name (rw)       |
| AsemanApp.organizationDomain     | Application organization domain (rw)     |
| AsemanApp.applicationAbout       | Short description about application (rw) |
| AsemanApp.applicationDisplayName | Display name of the application (rw)     |

## DesktopTools

Some tools and methods to do some actions on the Desktop operating systems

### System Dialogs

Using below methods you can work with system dialogs

| Method                              | Description                                                  |
| ----------------------------------- | ------------------------------------------------------------ |
| DesktopTools.getOpenFileName()      | Show open file dialog of the operating system                |
| DesktopTools.getOpenFileNames()     | Show open multiple file dialog of the operating system       |
| DesktopTools.getSaveFileName()      | Show save file dialog of the operating system                |
| DesktopTools.getExistingDirectory() | Show select directory dialog of the operating system         |
| DesktopTools.getFont()              | Show operating system font chooser dialog                    |
| DesktopTools.getColor()             | Show operating system color chooser dialog                   |
| DesktopTools.getText()              | Show operating system text input dialog (for example for file renaming) |
| DesktopTools.yesOrNo()              | Show simple message to choose between yes or no              |
| DesktopTools.showMessage()          | Show a simple information message with ok button             |

## Devices

`Devices` component provides many properties, methods and signal to work with device features like screen density, deviceId, device type and ...

### Screen related properties

Below properties return everything related to your screen and also operating system display settings

| Property                  | Description                                                  |
| ------------------------- | ------------------------------------------------------------ |
| Devices.screen            | Returns screen object (ro)                                   |
| Devices.lcdPhysicalSize   | Returns lcd size (ro)                                        |
| Devices.lcdPhysicalWidth  | Returns lcd width (ro)                                       |
| Devices.lcdPhysicalHeight | Returns lcd height (ro)                                      |
| Devices.lcdDpiX           | Returns lcd horizontal dpi (ro)                              |
| Devices.lcdDpiY           | Returns lcd vertical dpi (ro)                                |
| Devices.screenSize        | Returns screen resolution as QSize (ro)                      |
| Devices.densityDpi        | Returns density dpi of the screen (ro)                       |
| Devices.density           | Returns density value of the screen (ro)                     |
| Devices.deviceDensity     | Returns device density of the screen (ro)                    |
| Devices.fontDensity       | Returns suggested density for fonts (ro)                     |
| Devices.fontScale         | Scale all fonts that their size is related to Devices.fontDensity (rw) |

### Device type

To check device type on the QML source codes, use below properties

| Property               | Description                                                  |
| ---------------------- | ------------------------------------------------------------ |
| Devices.isMobile       | Returns true if device is mobile (ro)                        |
| Devices.isLargeTablet  | Returns true if device is a large tablet (ro)                |
| Devices.isTablet       | Returns true if device is any kind of tablet (ro)            |
| Devices.isTouchDevice  | Returns true if device is mobile or tablet (ro)              |
| Devices.isDesktop      | Returns true if device is any kind of desktop devices (mac or pc) (ro) |
| Devices.isMacX         | Returns true if device is mac (ro)                           |
| Devices.isWindows      | Returns true if device is windows (ro)                       |
| Devices.isWindows8     | Returns true if device is windows 8 (ro)                     |
| Devices.isLinux        | Returns true if device is any desktop linux distribution (ro) |
| Devices.isAndroid      | Returns true if device is android (ro)                       |
| Devices.isIOS          | Returns true if device is iOS (ro)                           |
| Devices.isUbuntuTouch  | Returns true if device is ubuntu touch device (ro)           |
| Devices.isWindowsPhone | Returns true if device is windows phone (ro)                 |

### Operating System Parts

To work with any parts of the operating system like statusbar, virtual keyboard and ..., Use below methods

| Property                         | Description                                                  |
| -------------------------------- | ------------------------------------------------------------ |
| Devices.transparentStatusBar     | Returns true if status-bar is transparented on Android (rw)  |
| Devices.transparentNavigationBar | Returns true if navigation-bar is transparented on Android (rw) |
| Devices.standardTitleBarHeight   | Returns standard and best suggested titleBar height (ro)     |
| Devices.statusBarHeight          | Returns status-bar height (ro)                               |
| Devices.navigationBarHeight      | Returns navigation-bar height (ro)                           |
| Devices.clipboard                | Returns clipboard contained text (rw)                        |
| Devices.clipboardUrl             | Returns clipboard contained urls (rw)                        |
| Devices.keyboardHeight           | Returns keyboard height (ro)                                 |
| Devices.keyboard                 | Returns true if keyboard is visible (ro)                     |
| Devices.hideKeyboard()           | Hide keyboard if it visible                                  |
| Devices.showKeyboard()           | Show keyboard if it hidden                                   |

