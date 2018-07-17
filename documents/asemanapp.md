# AsemanApp

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Enumerator](#enumerator)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>AsemanApp</font>|
|C++ class|<font color='#074885'>AsemanApplication</font>|
|Inherits|<font color='#074885'>[AsemanQuick](https://github.com/Aseman-Land/libqtelegram-aseman-edition/blob/API51/telegram/documents/types/asemanquick.md)</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>homePath</b></font>: string (readOnly)
* <font color='#074885'><b>startPath</b></font>: string (readOnly)
* <font color='#074885'><b>appPath</b></font>: string (readOnly)
* <font color='#074885'><b>appFilePath</b></font>: string (readOnly)
* <font color='#074885'><b>logPath</b></font>: string
* <font color='#074885'><b>confsPath</b></font>: string (readOnly)
* <font color='#074885'><b>tempPath</b></font>: string (readOnly)
* <font color='#074885'><b>backupsPath</b></font>: string (readOnly)
* <font color='#074885'><b>cameraPath</b></font>: string (readOnly)
* <font color='#074885'><b>appType</b></font>: int (readOnly)
* <font color='#074885'><b>isDebug</b></font>: boolean (readOnly)
* <font color='#074885'><b>globalFont</b></font>: QFont
* <font color='#074885'><b>applicationName</b></font>: string
* <font color='#074885'><b>applicationVersion</b></font>: string
* <font color='#074885'><b>organizationName</b></font>: string
* <font color='#074885'><b>organizationDomain</b></font>: string
* <font color='#074885'><b>applicationAbout</b></font>: string
* <font color='#074885'><b>applicationId</b></font>: string
* <font color='#074885'><b>windowIcon</b></font>: url
* <font color='#074885'><b>applicationState</b></font>: int (readOnly)
* <font color='#074885'><b>isRunning</b></font>: boolean (readOnly)
* <font color='#074885'><b>applicationDisplayName</b></font>: string
* <font color='#074885'><b>platformName</b></font>: string (readOnly)
* <font color='#074885'><b>quitOnLastWindowClosed</b></font>: boolean


### Methods

 * void <font color='#074885'><b>refreshTranslations</b></font>()
 * void <font color='#074885'><b>back</b></font>()
 * int <font color='#074885'><b>exec</b></font>()
 * void <font color='#074885'><b>exit</b></font>(int retcode)
 * void <font color='#074885'><b>exit</b></font>()
 * void <font color='#074885'><b>sleep</b></font>(qulonglong ms)
 * void <font color='#074885'><b>sendMessage</b></font>(string msg)
 * void <font color='#074885'><b>setSetting</b></font>(string key, variant value)
 * variant <font color='#074885'><b>readSetting</b></font>(string key, variant defaultValue)
 * variant <font color='#074885'><b>readSetting</b></font>(string key)


### Signals

 * void <font color='#074885'><b>globalFontFamilyChanged</b></font>()
 * void <font color='#074885'><b>globalMonoFontFamilyChanged</b></font>()
 * void <font color='#074885'><b>languageUpdated</b></font>()
 * void <font color='#074885'><b>backRequest</b></font>()
 * void <font color='#074885'><b>clickedOnDock</b></font>()
 * void <font color='#074885'><b>lastWindowClosed</b></font>()
 * void <font color='#074885'><b>messageReceived</b></font>(string msg)


### Enumerator


##### ApplicationType

|Key|Value|
|---|-----|
|NoneApplication|0|
|GuiApplication|1|
|CoreApplication|2|

##### ApplicationState

|Key|Value|
|---|-----|
|ApplicationSuspended|0|
|ApplicationHidden|1|
|ApplicationInactive|2|
|ApplicationActive|4|

