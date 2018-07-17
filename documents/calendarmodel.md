# CalendarModel

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
|Component|<font color='#074885'>CalendarModel</font>|
|C++ class|<font color='#074885'>AsemanCalendarModel</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>Yes</font>|


### Normal Properties

* <font color='#074885'><b>years</b></font>: QList<int> (readOnly)
* <font color='#074885'><b>months</b></font>: QList<int> (readOnly)
* <font color='#074885'><b>days</b></font>: QList<int> (readOnly)
* <font color='#074885'><b>hours</b></font>: QList<int> (readOnly)
* <font color='#074885'><b>minutes</b></font>: QList<int> (readOnly)
* <font color='#074885'><b>currentYearIndex</b></font>: int (readOnly)
* <font color='#074885'><b>currentMonthIndex</b></font>: int (readOnly)
* <font color='#074885'><b>currentDaysIndex</b></font>: int (readOnly)
* <font color='#074885'><b>currentHoursIndex</b></font>: int (readOnly)
* <font color='#074885'><b>currentMinutesIndex</b></font>: int (readOnly)
* <font color='#074885'><b>dateTime</b></font>: QDateTime
* <font color='#074885'><b>calendar</b></font>: int
* <font color='#074885'><b>minimum</b></font>: QDateTime
* <font color='#074885'><b>maximum</b></font>: QDateTime


### Methods

 * void <font color='#074885'><b>setConvertDate</b></font>(int yearIdx, int monthIdx, int dayIdx, int hourIdx, int minuteIdx)
 * string <font color='#074885'><b>monthName</b></font>(int month)


### Signals

 * void <font color='#074885'><b>secondsChanged</b></font>()


### Enumerator


##### CalendarTypes

|Key|Value|
|---|-----|
|CalendarGregorian|0|
|CalendarJalali|1|
|CalendarHijri|2|

