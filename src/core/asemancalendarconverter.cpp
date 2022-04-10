/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*!
    \class AsemanCalendarConverter
    \brief Provides Calendar manager and converter methods
    It supports Gregorian, Jalali and Hijri calendars.

    \reentrant
    \ingroup AsemanCore
 */

#include "asemancalendarconverter.h"
#include "asemancalendarconvertercore.h"

/*!
    \private
 */
class AsemanCalendarConverterPrivate
{
public:
    int calendar_type;
    AsemanCalendarConverterCore *calendar;
};

AsemanCalendarConverter::AsemanCalendarConverter(QObject *parent) :
    QObject(parent)
{
    p = new AsemanCalendarConverterPrivate;
    p->calendar_type = 0;
    p->calendar = new AsemanCalendarConverterCore();
}

/*!
    Sets current calendar type (Gregorian, Jalali, ...)

    \param t Calendar type
    \sa calendarIDs()
    \sa calendarName()
 */
void AsemanCalendarConverter::setCalendar(int t)
{
    if( p->calendar->calendar() == t )
        return;

    p->calendar->setCalendar( static_cast<AsemanCalendarConverterCore::CalendarTypes>(t) );
    Q_EMIT calendarChanged();
}


/*!
    Returns all calendar ids as a string list to use in setCalendar()

    \return All integer ids as StringList
    \sa setCalendar()
    \sa calendarName()
 */
QStringList AsemanCalendarConverter::calendarIDs() const
{
    QStringList res;
    res << QString::number(AsemanCalendarConverterCore::Gregorian);
    res << QString::number(AsemanCalendarConverterCore::Jalali);
    res << QString::number(AsemanCalendarConverterCore::Hijri);
    return res;
}


/*!
    Returns calendar name assigned to the \a t id.

    \param t Calendar type
    \sa setCalendar()
    \sa calendarIDs()
 */
QString AsemanCalendarConverter::calendarName(int t)
{
    switch( t )
    {
    case AsemanCalendarConverterCore::Gregorian:
        return QStringLiteral("Gregorian");
        break;
    case AsemanCalendarConverterCore::Jalali:
        return QStringLiteral("Jalali");
        break;
    case AsemanCalendarConverterCore::Hijri:
        return QStringLiteral("Hijri");
        break;
    }

    return QString();
}


/*!
    Returns current calendar type id.

    \return Calendar id
    \sa setCalendar()
    \sa calendarIDs()
 */
int AsemanCalendarConverter::calendar() const
{
    return p->calendar->calendar();
}


/*!
    Returns days from zero date (0001/01/01) of the current calendar.

    \return Days
    \sa setCalendar()
    \sa calendarIDs()
 */
int AsemanCalendarConverter::currentDays()
{
    return QDate(1,1,1).daysTo(QDate::currentDate());
}


/*!
    Converts and returns \a d parameter as day from zero date to the Date
    String based on the current calendar type.
    Convert format is "ddd MMM dd yy"

    \sa setCalendar()
    \sa currentDays()
    \sa convertIntToFullStringDate()
 */
QString AsemanCalendarConverter::convertIntToStringDate(qint64 d)
{
    return convertIntToStringDate(d,QStringLiteral("ddd MMM dd yy"));
}


/*!
    Converts and returns \a d parameter as day from zero date to the Date
    and longer String based on the current calendar type.
    Convert format is "ddd MMM dd yyyy"

    \sa setCalendar()
    \sa currentDays()
    \sa convertIntToStringDate()
 */
QString AsemanCalendarConverter::convertIntToFullStringDate(qint64 d)
{
    return convertIntToStringDate(d,QStringLiteral("ddd MMM dd yyyy"));
}


/*!
    Converts and returns \a d parameter as day from zero date to the Date
    and longer String based on the current calendar type.
    Convert format is "dd MM yy, dayOfWeek"

    \sa setCalendar()
    \sa currentDays()
    \sa convertIntToFullStringDate()
 */
QString AsemanCalendarConverter::convertIntToNumStringDate(qint64 d)
{
    QDate date = QDate(1,1,1);
    date = date.addDays(d);
    return ( p->calendar->numberString(date) );
}


/*!
    Translate int number to the local current calendar character.

    \sa setCalendar()
 */
QString AsemanCalendarConverter::translateInt(qint64 d)
{
    return (QString::number(d));
}


/*!
    Translate int number to the local current calendar character.

    \sa setCalendar()
 */
QString AsemanCalendarConverter::convertIntToStringDate(qint64 d, const QString &format)
{
    Q_UNUSED(format)
    QDate date = QDate(1,1,1);
    date = date.addDays(d);
    return ( p->calendar->historyString(date) );
}


/*!
    Converts date from \a y year, \a m month, \a d day to the
    QDate and gregorian object.

    \sa setCalendar()
 */
QDate AsemanCalendarConverter::convertDateToGragorian(qint64 y, int m, int d)
{
    return p->calendar->toDate(y,m,d);
}


/*!
    Converts \a t msec since epoch to the String date using convertDateTimeToString()
    Method.

    \sa setCalendar()
 */
QString AsemanCalendarConverter::fromMSecSinceEpoch(qint64 t)
{
    return convertDateTimeToString( QDateTime::fromMSecsSinceEpoch(t) );
}


/*!
    Converts \a dt QDateTime to the String date.

    \sa setCalendar()
    \sa fromMSecSinceEpoch()
 */
QString AsemanCalendarConverter::convertDateTimeToString(const QDateTime &dt)
{
    return ( p->calendar->paperString(dt) );
}


/*!
    Converts \a dt QDateTime to the String date.

    \sa setCalendar()
    \sa fromMSecSinceEpoch()
 */
QString AsemanCalendarConverter::convertDateTimeToString(const QDateTime &dt, const QString &format)
{
    return ( p->calendar->paperString(dt, format) );
}


/*!
    Converts \a dt QDate argument to the String date using convertDateTimeToLittleString()
    Method.

    \sa setCalendar()
    \sa fromMSecSinceEpoch()
 */
QString AsemanCalendarConverter::convertDateTimeToLittleString(const QDate &dt)
{
    return ( p->calendar->littleString(dt) );
}


/*!
    Returns days count of the month assigned to \a y year and \m month.
    Method.

    \sa setCalendar()
    \sa monthName()
 */
int AsemanCalendarConverter::daysOfMonth(qint64 y, int m)
{
    return p->calendar->daysOfMonth(y,m);
}


/*!
    Returns month name of \m month as a string.

    \sa setCalendar()
    \sa daysOfMonth()
 */
QString AsemanCalendarConverter::monthName(int m)
{
    return p->calendar->monthName(m);
}


/*!
    Merge QDate and QTime and returns them as a QDateTime object.
 */
QDateTime AsemanCalendarConverter::combineDateAndTime(const QDate &date, const QTime &time)
{
    return QDateTime(date, time);
}


/*!
    Returns month of the \a date object.
 */
int AsemanCalendarConverter::dateMonth(const QDate &date)
{
    return convertDate(date).month;
}


/*!
    Returns day of the \a date object.
 */
int AsemanCalendarConverter::dateDay(const QDate &date)
{
    return convertDate(date).day;
}


/*!
    Returns year of the \a date object.
 */
qint64 AsemanCalendarConverter::dateYear(const QDate &date)
{
    return convertDate(date).year;
}


/*!
    Returns year of the current date.
 */
qint64 AsemanCalendarConverter::currentYear()
{
    return p->calendar->getDate(QDate::currentDate()).year;
}


/*!
    Returns month of the current date.
 */
int AsemanCalendarConverter::currentMonth()
{
    return p->calendar->getDate(QDate::currentDate()).month;
}


/*!
    Returns day of the current date.
 */
int AsemanCalendarConverter::currentDay()
{
    return p->calendar->getDate(QDate::currentDate()).day;
}


/*!
    Converts date object to the DateProperty, contains all year,
    month and date properties.
 */
DateProperty AsemanCalendarConverter::convertDate(const QDate &date)
{
    return p->calendar->getDate(date);
}


/*!
    Converts \a days number to the current QDate object and Returns it.
 */
QDate AsemanCalendarConverter::convertDaysToDate(int days)
{
    return QDate(1,1,1).addDays(days);
}


/*!
    Converts \a date object as QDate and return days from 0001/01/01;
 */
int AsemanCalendarConverter::convertDateToDays(const QDate &date)
{
    return QDate(1,1,1).daysTo(date);
}


/*!
    Converts \a sec from unix zero time to the QDateTime object and Returns it.
 */
QDateTime AsemanCalendarConverter::fromTime_t(uint sec)
{
    return QDateTime::fromSecsSinceEpoch(sec);
}

AsemanCalendarConverter::~AsemanCalendarConverter()
{
    delete p->calendar;
    delete p;
}
