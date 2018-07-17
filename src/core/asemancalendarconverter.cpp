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

#include "asemancalendarconverter.h"
#include "asemancalendarconvertercore.h"

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

void AsemanCalendarConverter::setCalendar(int t)
{
    if( p->calendar->calendar() == t )
        return;

    p->calendar->setCalendar( static_cast<AsemanCalendarConverterCore::CalendarTypes>(t) );
    Q_EMIT calendarChanged();
}

QStringList AsemanCalendarConverter::calendarsID() const
{
    QStringList res;
    res << QString::number(AsemanCalendarConverterCore::Gregorian);
    res << QString::number(AsemanCalendarConverterCore::Jalali);
    res << QString::number(AsemanCalendarConverterCore::Hijri);
    return res;
}

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

int AsemanCalendarConverter::calendar() const
{
    return p->calendar->calendar();
}

int AsemanCalendarConverter::currentDays()
{
    return QDate(1,1,1).daysTo(QDate::currentDate());
}

QString AsemanCalendarConverter::convertIntToStringDate(qint64 d)
{
    return convertIntToStringDate(d,QStringLiteral("ddd MMM dd yy"));
}

QString AsemanCalendarConverter::convertIntToFullStringDate(qint64 d)
{
    return convertIntToStringDate(d,QStringLiteral("ddd MMM dd yyyy"));
}

QString AsemanCalendarConverter::convertIntToNumStringDate(qint64 d)
{
    QDate date = QDate(1,1,1);
    date = date.addDays(d);
    return ( p->calendar->numberString(date) );
}

QString AsemanCalendarConverter::translateInt(qint64 d)
{
    return (QString::number(d));
}

QString AsemanCalendarConverter::convertIntToStringDate(qint64 d, const QString &format)
{
    Q_UNUSED(format)
    QDate date = QDate(1,1,1);
    date = date.addDays(d);
    return ( p->calendar->historyString(date) );
}

QDate AsemanCalendarConverter::convertDateToGragorian(qint64 y, int m, int d)
{
    return p->calendar->toDate(y,m,d);
}

QString AsemanCalendarConverter::fromMSecSinceEpoch(qint64 t)
{
    return convertDateTimeToString( QDateTime::fromMSecsSinceEpoch(t) );
}

QString AsemanCalendarConverter::convertDateTimeToString(const QDateTime &dt)
{
    return ( p->calendar->paperString(dt) );
}

QString AsemanCalendarConverter::convertDateTimeToString(const QDateTime &dt, const QString &format)
{
    return ( p->calendar->paperString(dt, format) );
}

QString AsemanCalendarConverter::convertDateTimeToLittleString(const QDate &dt)
{
    return ( p->calendar->littleString(dt) );
}

int AsemanCalendarConverter::daysOfMonth(qint64 y, int m)
{
    return p->calendar->daysOfMonth(y,m);
}

QString AsemanCalendarConverter::monthName(int m)
{
    return p->calendar->monthName(m);
}

QDateTime AsemanCalendarConverter::combineDateAndTime(const QDate &date, const QTime &time)
{
    return QDateTime(date, time);
}

int AsemanCalendarConverter::dateMonth(const QDate &date)
{
    return convertDate(date).month;
}

int AsemanCalendarConverter::dateDay(const QDate &date)
{
    return convertDate(date).day;
}

qint64 AsemanCalendarConverter::dateYear(const QDate &date)
{
    return convertDate(date).year;
}

qint64 AsemanCalendarConverter::currentYear()
{
    return p->calendar->getDate(QDate::currentDate()).year;
}

int AsemanCalendarConverter::currentMonth()
{
    return p->calendar->getDate(QDate::currentDate()).month;
}

int AsemanCalendarConverter::currentDay()
{
    return p->calendar->getDate(QDate::currentDate()).day;
}

DateProperty AsemanCalendarConverter::convertDate(const QDate &date)
{
    return p->calendar->getDate(date);
}

QDate AsemanCalendarConverter::convertDaysToDate(int days)
{
    return QDate(1,1,1).addDays(days);
}

int AsemanCalendarConverter::convertDateToDays(const QDate &date)
{
    return QDate(1,1,1).daysTo(date);
}

QDateTime AsemanCalendarConverter::fromTime_t(uint sec)
{
    return QDateTime::fromTime_t(sec);
}

AsemanCalendarConverter::~AsemanCalendarConverter()
{
    delete p->calendar;
    delete p;
}
