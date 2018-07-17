# AudioRecorder

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Enumerator](#enumerator)
 * [Methods](#methods)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>AudioRecorder</font>|
|C++ class|<font color='#074885'>AsemanAudioRecorder</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>encoderSettings</b></font>: AsemanAudioEncoderSettings*
* <font color='#074885'><b>output</b></font>: url
* <font color='#074885'><b>mute</b></font>: boolean
* <font color='#074885'><b>available</b></font>: boolean (readOnly)
* <font color='#074885'><b>availability</b></font>: int (readOnly)
* <font color='#074885'><b>state</b></font>: int (readOnly)
* <font color='#074885'><b>status</b></font>: int (readOnly)
* <font color='#074885'><b>volume</b></font>: real
* <font color='#074885'><b>audioInput</b></font>: string
* <font color='#074885'><b>audioInputs</b></font>: list&lt;string&gt; (readOnly)


### Methods

 * void <font color='#074885'><b>stop</b></font>()
 * void <font color='#074885'><b>pause</b></font>()
 * void <font color='#074885'><b>record</b></font>()



### Enumerator


##### State

|Key|Value|
|---|-----|
|StoppedState|0|
|RecordingState|1|
|PausedState|2|

##### Status

|Key|Value|
|---|-----|
|UnavailableStatus|0|
|UnloadedStatus|1|
|LoadingStatus|2|
|LoadedStatus|3|
|StartingStatus|4|
|RecordingStatus|5|
|PausedStatus|6|
|FinalizingStatus|7|

