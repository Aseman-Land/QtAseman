# BackHandler

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>BackHandler</font>|
|C++ class|<font color='#074885'>AsemanBackHandler</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### [Usage](backhandlerusage.md)

### Normal Properties

* <font color='#074885'><b>topHandlerObject</b></font>: object (readOnly)
* <font color='#074885'><b>topHandlerMethod</b></font>: function(){[code]} (readOnly)
* <font color='#074885'><b>count</b></font>: int (readOnly)


### Methods

 * void <font color='#074885'><b>pushHandler</b></font>(object obj, function(){[code]} jsv)
 * void <font color='#074885'><b>pushDownHandler</b></font>(object obj, function(){[code]} jsv)
 * void <font color='#074885'><b>removeHandler</b></font>(object obj)
 * object <font color='#074885'><b>tryPopHandler</b></font>()
 * object <font color='#074885'><b>forcePopHandler</b></font>()
 * void <font color='#074885'><b>clear</b></font>()
 * boolean <font color='#074885'><b>back</b></font>()


### Signals

 * void <font color='#074885'><b>backFinished</b></font>()


