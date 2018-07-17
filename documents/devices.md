# Devices

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>Devices</font>|
|C++ class|<font color='#074885'>AsemanDevices</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>isMobile</b></font>: boolean (readOnly)
* <font color='#074885'><b>isTablet</b></font>: boolean (readOnly)
* <font color='#074885'><b>isLargeTablet</b></font>: boolean (readOnly)
* <font color='#074885'><b>isTouchDevice</b></font>: boolean (readOnly)
* <font color='#074885'><b>isDesktop</b></font>: boolean (readOnly)
* <font color='#074885'><b>isMacX</b></font>: boolean (readOnly)
* <font color='#074885'><b>isWindows</b></font>: boolean (readOnly)
* <font color='#074885'><b>isWindows8</b></font>: boolean (readOnly)
* <font color='#074885'><b>isLinux</b></font>: boolean (readOnly)
* <font color='#074885'><b>isAndroid</b></font>: boolean (readOnly)
* <font color='#074885'><b>isIOS</b></font>: boolean (readOnly)
* <font color='#074885'><b>isUbuntuTouch</b></font>: boolean (readOnly)
* <font color='#074885'><b>isWindowsPhone</b></font>: boolean (readOnly)
* <font color='#074885'><b>screen</b></font>: object (readOnly)
* <font color='#074885'><b>cameraIsAvailable</b></font>: boolean (readOnly)
* <font color='#074885'><b>lcdPhysicalSize</b></font>: real (readOnly)
* <font color='#074885'><b>lcdPhysicalWidth</b></font>: real (readOnly)
* <font color='#074885'><b>lcdPhysicalHeight</b></font>: real (readOnly)
* <font color='#074885'><b>lcdDpiX</b></font>: real (readOnly)
* <font color='#074885'><b>lcdDpiY</b></font>: real (readOnly)
* <font color='#074885'><b>screenSize</b></font>: size (readOnly)
* <font color='#074885'><b>keyboardHeight</b></font>: real (readOnly)
* <font color='#074885'><b>localFilesPrePath</b></font>: string (readOnly)
* <font color='#074885'><b>densityDpi</b></font>: int (readOnly)
* <font color='#074885'><b>density</b></font>: real (readOnly)
* <font color='#074885'><b>deviceDensity</b></font>: real (readOnly)
* <font color='#074885'><b>fontDensity</b></font>: real (readOnly)
* <font color='#074885'><b>transparentStatusBar</b></font>: boolean (readOnly)
* <font color='#074885'><b>transparentNavigationBar</b></font>: boolean (readOnly)
* <font color='#074885'><b>standardTitleBarHeight</b></font>: real (readOnly)
* <font color='#074885'><b>statusBarHeight</b></font>: real (readOnly)
* <font color='#074885'><b>navigationBarHeight</b></font>: real (readOnly)
* <font color='#074885'><b>clipboard</b></font>: string
* <font color='#074885'><b>clipboardUrl</b></font>: QList<QUrl>
* <font color='#074885'><b>keyboard</b></font>: boolean (readOnly)
* <font color='#074885'><b>cameraLocation</b></font>: string (readOnly)
* <font color='#074885'><b>picturesLocation</b></font>: string (readOnly)
* <font color='#074885'><b>musicsLocation</b></font>: string (readOnly)
* <font color='#074885'><b>documentsLocation</b></font>: string (readOnly)
* <font color='#074885'><b>downloadsLocation</b></font>: string (readOnly)
* <font color='#074885'><b>resourcePath</b></font>: string (readOnly)
* <font color='#074885'><b>libsPath</b></font>: string (readOnly)
* <font color='#074885'><b>deviceName</b></font>: string (readOnly)
* <font color='#074885'><b>deviceId</b></font>: string (readOnly)


### Methods

 * void <font color='#074885'><b>hideKeyboard</b></font>()
 * void <font color='#074885'><b>showKeyboard</b></font>()
 * void <font color='#074885'><b>share</b></font>(string subject, string message)
 * void <font color='#074885'><b>openFile</b></font>(string address)
 * void <font color='#074885'><b>shareFile</b></font>(string address)
 * void <font color='#074885'><b>callNumber</b></font>(string number)
 * void <font color='#074885'><b>setClipboard</b></font>(string text)
 * void <font color='#074885'><b>setClipboardData</b></font>(AsemanMimeData* mime)
 * boolean <font color='#074885'><b>startCameraPicture</b></font>()
 * boolean <font color='#074885'><b>getOpenPictures</b></font>()


### Signals

 * void <font color='#074885'><b>incomingShare</b></font>(string title, string msg)
 * void <font color='#074885'><b>incomingImage</b></font>(string path)
 * void <font color='#074885'><b>selectImageResult</b></font>(string path)
 * void <font color='#074885'><b>activityPaused</b></font>()
 * void <font color='#074885'><b>activityResumed</b></font>()


