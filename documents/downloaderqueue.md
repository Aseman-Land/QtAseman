# DownloaderQueue

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>DownloaderQueue</font>|
|C++ class|<font color='#074885'>AsemanFileDownloaderQueue</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>capacity</b></font>: int
* <font color='#074885'><b>destination</b></font>: string


### Methods

 * void <font color='#074885'><b>download</b></font>(string url, string fileName)


### Signals

 * void <font color='#074885'><b>finished</b></font>(string url, string fileName)
 * void <font color='#074885'><b>progressChanged</b></font>(string url, string fileName, real percent)


