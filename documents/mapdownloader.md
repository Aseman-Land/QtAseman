# MapDownloader

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Enumerator](#enumerator)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>MapDownloader</font>|
|C++ class|<font color='#074885'>AsemanMapDownloader</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>destination</b></font>: url
* <font color='#074885'><b>image</b></font>: url (readOnly)
* <font color='#074885'><b>currentGeo</b></font>: point (readOnly)
* <font color='#074885'><b>mapProvider</b></font>: int
* <font color='#074885'><b>size</b></font>: size
* <font color='#074885'><b>zoom</b></font>: int
* <font color='#074885'><b>downloading</b></font>: boolean (readOnly)


### Methods

 * void <font color='#074885'><b>download</b></font>(point geo)
 * boolean <font color='#074885'><b>check</b></font>(point geo)
 * string <font color='#074885'><b>linkOf</b></font>(point geo)
 * string <font color='#074885'><b>webLinkOf</b></font>(point geo)
 * string <font color='#074885'><b>pathOf</b></font>(point geo)


### Signals

 * void <font color='#074885'><b>finished</b></font>()


### Enumerator


##### MapProvider

|Key|Value|
|---|-----|
|MapProviderGoogle|0|

