# AsemanSensors

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Enumerator](#enumerator)
 * [Methods](#methods)
 * [Signals](#signals)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>AsemanSensors</font>|
|C++ class|<font color='#074885'>AsemanSensors</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>ax</b></font>: real (readOnly)
* <font color='#074885'><b>ay</b></font>: real (readOnly)
* <font color='#074885'><b>az</b></font>: real (readOnly)
* <font color='#074885'><b>gx</b></font>: real (readOnly)
* <font color='#074885'><b>gy</b></font>: real (readOnly)
* <font color='#074885'><b>gz</b></font>: real (readOnly)
* <font color='#074885'><b>angleX</b></font>: real (readOnly)
* <font color='#074885'><b>angleY</b></font>: real (readOnly)
* <font color='#074885'><b>angleZ</b></font>: real (readOnly)
* <font color='#074885'><b>zeroAngleX</b></font>: real (readOnly)
* <font color='#074885'><b>zeroAngleY</b></font>: real (readOnly)
* <font color='#074885'><b>zeroAngleZ</b></font>: real (readOnly)
* <font color='#074885'><b>angleSpeedX</b></font>: real (readOnly)
* <font color='#074885'><b>angleSpeedY</b></font>: real (readOnly)
* <font color='#074885'><b>angleSpeedZ</b></font>: real (readOnly)
* <font color='#074885'><b>duration</b></font>: int
* <font color='#074885'><b>active</b></font>: boolean
* <font color='#074885'><b>activeSensors</b></font>: int


### Methods

 * void <font color='#074885'><b>start</b></font>()
 * void <font color='#074885'><b>stop</b></font>()
 * void <font color='#074885'><b>zero</b></font>()
 * void <font color='#074885'><b>setZero</b></font>(real xrad, real zrad)
 * void <font color='#074885'><b>refresh</b></font>()


### Signals

 * void <font color='#074885'><b>updated</b></font>()


### Enumerator


##### SensorType

|Key|Value|
|---|-----|
|RotationSensor|1|
|GravitySensor|2|
|AccelerometerSensor|4|
|GyroscopeSensor|8|
|AllSensors|15|

