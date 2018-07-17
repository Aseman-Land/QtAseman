# StoreManager

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Enumerator](#enumerator)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>StoreManager</font>|
|C++ class|<font color='#074885'>AsemanStoreManager</font>|
|Inherits|<font color='#074885'>[AsemanQuick](https://github.com/Aseman-Land/libqtelegram-aseman-edition/blob/API51/telegram/documents/types/asemanquick.md)</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>publicKey</b></font>: string
* <font color='#074885'><b>packageName</b></font>: string
* <font color='#074885'><b>bindIntent</b></font>: string
* <font color='#074885'><b>cacheSource</b></font>: string


### Methods

 * boolean <font color='#074885'><b>setup</b></font>()


### Signals

 * void <font color='#074885'><b>itemDetailsChanged</b></font>()
 * void <font color='#074885'><b>inventoryStateChanged</b></font>(string sku)
 * void <font color='#074885'><b>inventoryPurchased</b></font>(string sku)


### Enumerator


##### InventoryState

|Key|Value|
|---|-----|
|InventoryStateNone|0|
|InventoryStatePurchasing|1|
|InventoryStatePurchased|2|

