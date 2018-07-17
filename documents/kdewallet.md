# KdeWallet

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>KdeWallet</font>|
|C++ class|<font color='#074885'>AsemanKdeWallet</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>availableWallets</b></font>: list&lt;string&gt; (readOnly)
* <font color='#074885'><b>opened</b></font>: boolean (readOnly)
* <font color='#074885'><b>wallet</b></font>: string
* <font color='#074885'><b>folderList</b></font>: list&lt;string&gt; (readOnly)


### Methods

 * boolean <font color='#074885'><b>createFolder</b></font>(string name)
 * boolean <font color='#074885'><b>removeFolder</b></font>(string name)
 * byte <font color='#074885'><b>readEntry</b></font>(string folder, string key)
 * map <font color='#074885'><b>readEntryList</b></font>(string folder, string key)
 * byte <font color='#074885'><b>readMap</b></font>(string folder, string key)
 * map <font color='#074885'><b>readMapList</b></font>(string folder, string key)
 * string <font color='#074885'><b>readPassword</b></font>(string folder, string key)
 * map <font color='#074885'><b>readPasswordList</b></font>(string folder, string key)
 * int <font color='#074885'><b>removeEntry</b></font>(string folder, string key)
 * int <font color='#074885'><b>renameEntry</b></font>(string folder, string oldName, string newName)
 * int <font color='#074885'><b>writeEntry</b></font>(string folder, string key, byte value)
 * int <font color='#074885'><b>writeEntry</b></font>(string folder, string key, byte value, int entryType)
 * int <font color='#074885'><b>writeMap</b></font>(string folder, string key, byte value)
 * int <font color='#074885'><b>writePassword</b></font>(string folder, string key, string value)
 * boolean <font color='#074885'><b>hasEntry</b></font>(string folder, string key)
 * boolean <font color='#074885'><b>hasFolder</b></font>(string folder)
 * boolean <font color='#074885'><b>open</b></font>()
 * boolean <font color='#074885'><b>close</b></font>()



