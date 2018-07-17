# SystemTray

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Enumerator](#enumerator)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>SystemTray</font>|
|C++ class|<font color='#074885'>AsemanSystemTray</font>|
|Inherits|<font color='#074885'>[AsemanQuick](https://github.com/Aseman-Land/libqtelegram-aseman-edition/blob/API51/telegram/documents/types/asemanquick.md)</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>visible</b></font>: boolean
* <font color='#074885'><b>icon</b></font>: url
* <font color='#074885'><b>badgeCount</b></font>: int
* <font color='#074885'><b>badgeFillColor</b></font>: QColor
* <font color='#074885'><b>badgeStrokeColor</b></font>: QColor
* <font color='#074885'><b>badgeTextColor</b></font>: QColor
* <font color='#074885'><b>menu</b></font>: list&lt;string&gt;



### Signals

 * void <font color='#074885'><b>activated</b></font>(int reason)
 * void <font color='#074885'><b>menuTriggered</b></font>(int index)


### Enumerator


##### ActivateReason

|Key|Value|
|---|-----|
|ActivateUnknown|0|
|ActivateContext|1|
|ActivateDoubleClick|2|
|ActivateTrigger|3|
|ActivateMiddleClick|4|

