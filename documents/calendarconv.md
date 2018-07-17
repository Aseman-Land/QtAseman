# CalendarConv

 * [Component details](#component-details)
 * [Normal Properties](#normal-properties)
 * [Methods](#methods)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>CalendarConv</font>|
|C++ class|<font color='#074885'>AsemanCalendarConverter</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|


### Normal Properties

* <font color='#074885'><b>calendar</b></font>: int
* <font color='#074885'><b>calendarsID</b></font>: list&lt;string&gt; (readOnly)
* <font color='#074885'><b>currentDays</b></font>: int (readOnly)
* <font color='#074885'><b>currentYear</b></font>: int (readOnly)
* <font color='#074885'><b>currentMonth</b></font>: int (readOnly)
* <font color='#074885'><b>currentDay</b></font>: int (readOnly)


### Methods

 * string <font color='#074885'><b>calendarName</b></font>(int t)
 * string <font color='#074885'><b>convertIntToStringDate</b></font>(qlonglong d)
 * string <font color='#074885'><b>convertIntToFullStringDate</b></font>(qlonglong d)
 * string <font color='#074885'><b>convertIntToNumStringDate</b></font>(qlonglong d)
 * string <font color='#074885'><b>translateInt</b></font>(qlonglong d)
 * string <font color='#074885'><b>convertIntToStringDate</b></font>(qlonglong d, string format)
 * QDate <font color='#074885'><b>convertDateToGragorian</b></font>(qlonglong year, int month, int day)
 * string <font color='#074885'><b>fromMSecSinceEpoch</b></font>(qlonglong t)
 * string <font color='#074885'><b>convertDateTimeToString</b></font>(QDateTime dt)
 * string <font color='#074885'><b>convertDateTimeToString</b></font>(QDateTime dt, string format)
 * string <font color='#074885'><b>convertDateTimeToLittleString</b></font>(QDate dt)
 * int <font color='#074885'><b>daysOfMonth</b></font>(qlonglong year, int month)
 * string <font color='#074885'><b>monthName</b></font>(int month)
 * QDateTime <font color='#074885'><b>combineDateAndTime</b></font>(QDate date, QTime time)
 * int <font color='#074885'><b>dateMonth</b></font>(QDate date)
 * int <font color='#074885'><b>dateDay</b></font>(QDate date)
 * qlonglong <font color='#074885'><b>dateYear</b></font>(QDate date)
 * QDate <font color='#074885'><b>convertDaysToDate</b></font>(int days)
 * int <font color='#074885'><b>convertDateToDays</b></font>(QDate date)
 * QDateTime <font color='#074885'><b>fromTime_t</b></font>(uint sec)



