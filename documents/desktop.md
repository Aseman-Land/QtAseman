# Desktop

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Enumerator](#enumerator)
 * [Methods](#methods)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>Desktop</font>|
|C++ class|<font color='#074885'>AsemanDesktopTools</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>titleBarColor</b></font>: QColor (readOnly)
* <font color='#074885'><b>titleBarTransparentColor</b></font>: QColor (readOnly)
* <font color='#074885'><b>titleBarTextColor</b></font>: QColor (readOnly)
* <font color='#074885'><b>titleBarIsDark</b></font>: boolean (readOnly)
* <font color='#074885'><b>desktopSession</b></font>: int (readOnly)
* <font color='#074885'><b>fontFamilies</b></font>: list&lt;string&gt; (readOnly)
* <font color='#074885'><b>menuStyle</b></font>: string
* <font color='#074885'><b>currentMenuObject</b></font>: object (readOnly)
* <font color='#074885'><b>tooltip</b></font>: string


### Methods

 * string <font color='#074885'><b>getOpenFileName</b></font>(QWindow* window, string title, string filter, string startPath)
 * string <font color='#074885'><b>getOpenFileName</b></font>(QWindow* window, string title, string filter)
 * string <font color='#074885'><b>getOpenFileName</b></font>(QWindow* window, string title)
 * string <font color='#074885'><b>getOpenFileName</b></font>(QWindow* window)
 * string <font color='#074885'><b>getOpenFileName</b></font>()
 * list&lt;string&gt; <font color='#074885'><b>getOpenFileNames</b></font>(QWindow* window, string title, string filter, string startPath)
 * list&lt;string&gt; <font color='#074885'><b>getOpenFileNames</b></font>(QWindow* window, string title, string filter)
 * list&lt;string&gt; <font color='#074885'><b>getOpenFileNames</b></font>(QWindow* window, string title)
 * list&lt;string&gt; <font color='#074885'><b>getOpenFileNames</b></font>(QWindow* window)
 * list&lt;string&gt; <font color='#074885'><b>getOpenFileNames</b></font>()
 * string <font color='#074885'><b>getSaveFileName</b></font>(QWindow* window, string title, string filter, string startPath)
 * string <font color='#074885'><b>getSaveFileName</b></font>(QWindow* window, string title, string filter)
 * string <font color='#074885'><b>getSaveFileName</b></font>(QWindow* window, string title)
 * string <font color='#074885'><b>getSaveFileName</b></font>(QWindow* window)
 * string <font color='#074885'><b>getSaveFileName</b></font>()
 * string <font color='#074885'><b>getExistingDirectory</b></font>(QWindow* window, string title, string startPath)
 * string <font color='#074885'><b>getExistingDirectory</b></font>(QWindow* window, string title)
 * string <font color='#074885'><b>getExistingDirectory</b></font>(QWindow* window)
 * string <font color='#074885'><b>getExistingDirectory</b></font>()
 * QFont <font color='#074885'><b>getFont</b></font>(QWindow* window, string title, QFont font)
 * QFont <font color='#074885'><b>getFont</b></font>(QWindow* window, string title)
 * QFont <font color='#074885'><b>getFont</b></font>(QWindow* window)
 * QFont <font color='#074885'><b>getFont</b></font>()
 * QColor <font color='#074885'><b>getColor</b></font>(QColor color)
 * QColor <font color='#074885'><b>getColor</b></font>()
 * string <font color='#074885'><b>getText</b></font>(QWindow* window, string title, string text, string defaultText)
 * string <font color='#074885'><b>getText</b></font>(QWindow* window, string title, string text)
 * string <font color='#074885'><b>getText</b></font>(QWindow* window, string title)
 * string <font color='#074885'><b>getText</b></font>(QWindow* window)
 * string <font color='#074885'><b>getText</b></font>()
 * int <font color='#074885'><b>showMenu</b></font>(list&lt;variant&gt; actions, point point)
 * int <font color='#074885'><b>showMenu</b></font>(list&lt;variant&gt; actions)
 * boolean <font color='#074885'><b>yesOrNo</b></font>(QWindow* window, string title, string text, int type)
 * boolean <font color='#074885'><b>yesOrNo</b></font>(QWindow* window, string title, string text)
 * void <font color='#074885'><b>showMessage</b></font>(QWindow* window, string title, string text, int type)
 * void <font color='#074885'><b>showMessage</b></font>(QWindow* window, string title, string text)



### Enumerator


##### DesktopSession

|Key|Value|
|---|-----|
|Unknown|0|
|Gnome|1|
|GnomeFallBack|2|
|Unity|3|
|Kde|4|
|Plasma|5|
|Windows|6|
|Mac|7|

##### YesOrNoType

|Key|Value|
|---|-----|
|Warning|0|
|Question|1|
|Information|2|
|Critical|3|

