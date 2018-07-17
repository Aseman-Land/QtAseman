# FileSystemModel

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Enumerator](#enumerator)
 * [Methods](#methods)
 * [Signals](#signals)
 * [Roles](#roles)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>FileSystemModel</font>|
|C++ class|<font color='#074885'>AsemanFileSystemModel</font>|
|Inherits|<font color='#074885'>AsemanAbstractListModel</font>|
|Model|<font color='#074885'>Yes</font>|


### Normal Properties

* <font color='#074885'><b>showDirs</b></font>: boolean
* <font color='#074885'><b>showDotAndDotDot</b></font>: boolean
* <font color='#074885'><b>showDirsFirst</b></font>: boolean
* <font color='#074885'><b>showFiles</b></font>: boolean
* <font color='#074885'><b>showHidden</b></font>: boolean
* <font color='#074885'><b>nameFilters</b></font>: list&lt;string&gt;
* <font color='#074885'><b>folder</b></font>: string
* <font color='#074885'><b>parentFolder</b></font>: string (readOnly)
* <font color='#074885'><b>sortField</b></font>: int
* <font color='#074885'><b>count</b></font>: int (readOnly)


### Methods

 * void <font color='#074885'><b>refresh</b></font>()


### Signals

 * void <font color='#074885'><b>listChanged</b></font>()


### Enumerator


##### SortFlag

|Key|Value|
|---|-----|
|Name|0|
|Size|1|
|Date|2|

##### DataRole

|Key|Value|
|---|-----|
|FilePath|256|
|FileUrl|257|
|FileName|258|
|FileMime|259|
|FileSize|260|
|FileSuffix|261|
|FileBaseName|262|
|FileIsDir|263|
|FileModifiedDate|264|
|FileCreatedDate|265|


### Roles

 * model.<font color='#074885'>filePath</font>
 * model.<font color='#074885'>fileUrl</font>
 * model.<font color='#074885'>fileName</font>
 * model.<font color='#074885'>fileMime</font>
 * model.<font color='#074885'>fileSize</font>
 * model.<font color='#074885'>fileSuffix</font>
 * model.<font color='#074885'>fileBaseName</font>
 * model.<font color='#074885'>fileIsDir</font>
 * model.<font color='#074885'>fileModifiedDate</font>
 * model.<font color='#074885'>fileCreatedDate</font>
