# WebPageGrabber

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>WebPageGrabber</font>|
|C++ class|<font color='#074885'>AsemanWebPageGrabber</font>|
|Inherits|<font color='#074885'>[AsemanQuick](https://github.com/Aseman-Land/libqtelegram-aseman-edition/blob/API51/telegram/documents/types/asemanquick.md)</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>source</b></font>: url
* <font color='#074885'><b>destination</b></font>: string
* <font color='#074885'><b>timeOut</b></font>: int
* <font color='#074885'><b>running</b></font>: boolean (readOnly)
* <font color='#074885'><b>isAvailable</b></font>: boolean (readOnly)


### Methods

 * void <font color='#074885'><b>start</b></font>(boolean force)
 * void <font color='#074885'><b>start</b></font>()
 * url <font color='#074885'><b>check</b></font>(url source, QString* destPath)
 * url <font color='#074885'><b>check</b></font>(url source)


### Signals

 * void <font color='#074885'><b>complete</b></font>(QImage image)
 * void <font color='#074885'><b>finished</b></font>(url path)


