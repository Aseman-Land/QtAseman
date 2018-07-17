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

#include "asemancalendarmodel.h"

#include <QTimer>
#include <QDebug>

class AsemanCalendarModelPrivate
{
public:
    AsemanCalendarConverter *conv;
    QDateTime dateTime;
    QDateTime minimum;
    QDateTime maximum;
    int calendar;

    QList<int> years;
    QList<int> months;
    QList<int> days;
    QList<int> hours;
    QList<int> minutes;

    int currentYearIndex;
    int currentMonthIndex;
    int currentDaysIndex;
    int currentHoursIndex;
    int currentMinutesIndex;

    QTimer *refreshTimer;
};

AsemanCalendarModel::AsemanCalendarModel(QObject *parent) :
    QObject(parent)
{
    p = new AsemanCalendarModelPrivate;
    p->calendar = CalendarGregorian;
    p->currentYearIndex = 0;
    p->currentMonthIndex = 0;
    p->currentDaysIndex = 0;
    p->currentHoursIndex = 0;
    p->currentMinutesIndex = 0;

    p->dateTime = QDateTime::currentDateTime();
    p->minimum = p->dateTime.addYears(-100);
    p->maximum = p->dateTime.addYears(100);

    p->conv = new AsemanCalendarConverter(this);
    p->conv->setCalendar(p->calendar);

    p->refreshTimer = new QTimer(this);
    p->refreshTimer->setSingleShot(true);
    p->refreshTimer->setInterval(100);

    connect(p->refreshTimer, &QTimer::timeout, this, &AsemanCalendarModel::refreshLists_prv);

    refreshLists_prv();
}

QList<int> AsemanCalendarModel::years() const
{
    return p->years;
}

QList<int> AsemanCalendarModel::months() const
{
    return p->months;
}

QList<int> AsemanCalendarModel::days() const
{
    return p->days;
}

QList<int> AsemanCalendarModel::hours() const
{
    return p->hours;
}

QList<int> AsemanCalendarModel::minutes() const
{
    return p->minutes;
}

int AsemanCalendarModel::currentYearIndex() const
{
    return p->currentYearIndex;
}

int AsemanCalendarModel::currentMonthIndex() const
{
    return p->currentMonthIndex;
}

int AsemanCalendarModel::currentDaysIndex() const
{
    return p->currentDaysIndex;
}

int AsemanCalendarModel::currentHoursIndex() const
{
    return p->currentHoursIndex;
}

int AsemanCalendarModel::currentMinutesIndex() const
{
    return p->currentMinutesIndex;
}

void AsemanCalendarModel::setDateTime(const QDateTime &dt)
{
    if(p->dateTime == dt)
        return;

    p->dateTime = dt;
    if(p->dateTime < p->minimum)
        p->dateTime = p->minimum;
    else
    if(p->dateTime > p->maximum)
        p->dateTime = p->maximum;

    refreshLists();
    Q_EMIT dateTimeChanged();
}

QDateTime AsemanCalendarModel::dateTime() const
{
    return p->dateTime;
}

void AsemanCalendarModel::setCalendar(int t)
{
    if(p->calendar == t)
        return;

    p->calendar = t;
    p->conv->setCalendar(t);

    refreshLists_prv();
    Q_EMIT calendarChanged();
}

int AsemanCalendarModel::calendar() const
{
    return p->calendar;
}

void AsemanCalendarModel::setMinimum(const QDateTime &dt)
{
    if(p->minimum == dt)
        return;

    p->minimum = dt;
    if(p->minimum > p->maximum)
        p->minimum = p->maximum;

    refreshLists();
    Q_EMIT minimumChanged();

    if(p->dateTime < p->minimum)
    {
        p->dateTime = p->minimum;
        Q_EMIT dateTimeChanged();
    }
}

QDateTime AsemanCalendarModel::minimum() const
{
    return p->minimum;
}

void AsemanCalendarModel::setMaximum(const QDateTime &dt)
{
    if(p->maximum == dt)
        return;

    p->maximum = dt;
    if(p->minimum > p->maximum)
        p->maximum = p->minimum;

    refreshLists();
    Q_EMIT maximumChanged();

    if(p->dateTime > p->maximum)
    {
        p->dateTime = p->maximum;
        refreshLists();
        Q_EMIT dateTimeChanged();
    }
}

QDateTime AsemanCalendarModel::maximum() const
{
    return p->maximum;
}

void AsemanCalendarModel::setConvertDate(int yearIdx, int monthIdx, int dayIdx, int hourIdx, int minuteIdx)
{
    if(yearIdx < 0 || yearIdx > p->years.length())
        return;
    if(monthIdx < 0 || monthIdx > p->months.length())
        return;
    if(dayIdx < 0 || dayIdx > p->days.length())
        return;
    if(hourIdx < 0 || hourIdx > p->hours.length())
        return;
    if(minuteIdx < 0 || minuteIdx > p->minutes.length())
        return;

    int year = p->years.at(yearIdx);
    int month = p->months.at(monthIdx);
    int day = p->days.at(dayIdx);
    int hour = p->hours.at(hourIdx);
    int minute = p->minutes.at(minuteIdx);

    const QDate &date = p->conv->convertDateToGragorian(year, month, day);
    setDateTime( QDateTime(date, QTime(hour, minute)) );
}

QString AsemanCalendarModel::monthName(int month)
{
    return p->conv->monthName(month);
}

void AsemanCalendarModel::refreshLists()
{
    p->refreshTimer->stop();
    p->refreshTimer->start();
}

void AsemanCalendarModel::refreshLists_prv()
{
    const DateProperty &min = p->conv->convertDate(p->minimum.date());
    const DateProperty &max = p->conv->convertDate(p->maximum.date());
    const DateProperty &dt = p->conv->convertDate(p->dateTime.date());


    QList<int> years;
    qint64 yearStart = min.year;
    qint64 yearEnd = max.year;
    for(qint64 i=yearStart; i<=yearEnd; i++)
        years << i;

    QList<int> months;
    int monthStart = (min.year == dt.year? min.month : 1);
    int monthEnd = (max.year == dt.year? max.month : 12);
    for(int i=monthStart; i<=monthEnd; i++)
        months << i;

    QList<int> days;
    int dayStart = (min.year == dt.year && min.month == dt.month? min.day : 1);
    int dayEnd = (max.year == dt.year && max.month == dt.month? max.day : p->conv->daysOfMonth(dt.year, dt.month));
    for(int i=dayStart; i<=dayEnd; i++)
        days << i;

    QList<int> hours;
    int hourStart = (min==dt? p->minimum.time().hour() : 0);
    int hourEnd = (max==dt? p->maximum.time().hour() : 23);
    for(int i=hourStart; i<=hourEnd; i++)
        hours << i;

    QList<int> minutes;
    int minuteStart = (min==dt && p->minimum.time().hour() == p->dateTime.time().hour()? p->minimum.time().minute() : 0);
    int minuteEnd = (max==dt && p->minimum.time().hour() == p->dateTime.time().hour()? p->maximum.time().minute() : 59);
    for(int i=minuteStart; i<=minuteEnd; i++)
        minutes << i;

    int currentYearIndex = dt.year - yearStart;
    int currentMonthIndex = dt.month - monthStart;
    int currentDaysIndex = dt.day - dayStart;
    int currentHoursIndex = p->dateTime.time().hour() - hourStart;
    int currentMinutesIndex = p->dateTime.time().minute() - minuteStart;

    bool years_changed = (p->years != years);
    bool months_changed = (p->months != months);
    bool days_changed = (p->days != days);
    bool hours_changed = (p->hours != hours);
    bool minutes_changed = (p->minutes != minutes);
    bool currentYearIndex_changed = (p->currentYearIndex != currentYearIndex);
    bool currentMonthIndex_changed = (p->currentMonthIndex != currentMonthIndex);
    bool currentDaysIndex_changed = (p->currentDaysIndex != currentDaysIndex);
    bool currentHoursIndex_changed = (p->currentHoursIndex != currentHoursIndex);
    bool currentMinutesIndex_changed = (p->currentMinutesIndex != currentMinutesIndex);

    p->years = years;
    p->months = months;
    p->days = days;
    p->hours = hours;
    p->minutes = minutes;
    p->currentYearIndex = currentYearIndex;
    p->currentMonthIndex = currentMonthIndex;
    p->currentDaysIndex = currentDaysIndex;
    p->currentHoursIndex = currentHoursIndex;
    p->currentMinutesIndex = currentMinutesIndex;

    if(years_changed) Q_EMIT yearsChanged();
    if(months_changed) Q_EMIT monthsChanged();
    if(days_changed) Q_EMIT daysChanged();
    if(hours_changed) Q_EMIT hoursChanged();
    if(minutes_changed) Q_EMIT minutesChanged();
    if(currentYearIndex_changed || years_changed) Q_EMIT currentYearIndexChanged();
    if(currentMonthIndex_changed || months_changed) Q_EMIT currentMonthIndexChanged();
    if(currentDaysIndex_changed || days_changed) Q_EMIT currentDaysIndexChanged();
    if(currentHoursIndex_changed || hours_changed) Q_EMIT currentHoursIndexChanged();
    if(currentMinutesIndex_changed || minutes_changed) Q_EMIT currentMinutesIndexChanged();
}

AsemanCalendarModel::~AsemanCalendarModel()
{
    delete p;
}
