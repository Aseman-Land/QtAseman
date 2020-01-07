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

#ifndef ASEMANCALENDARMODEL_H
#define ASEMANCALENDARMODEL_H

#include <QObject>
#include <QStringList>
#include <QDateTime>

#include "asemancalendarconverter.h"

#include "asemancore_global.h"

class AsemanCalendarModelPrivate;
class LIBQTASEMAN_CORE_EXPORT AsemanCalendarModel : public QObject
{
    Q_OBJECT
    Q_ENUMS(CalendarTypes)

    Q_PROPERTY(QList<int> years   READ years   NOTIFY yearsChanged)
    Q_PROPERTY(QList<int> months  READ months  NOTIFY monthsChanged)
    Q_PROPERTY(QList<int> days    READ days    NOTIFY daysChanged)
    Q_PROPERTY(QList<int> hours   READ hours   NOTIFY hoursChanged)
    Q_PROPERTY(QList<int> minutes READ minutes NOTIFY minutesChanged)

    Q_PROPERTY(int currentYearIndex    READ currentYearIndex    NOTIFY currentYearIndexChanged   )
    Q_PROPERTY(int currentMonthIndex   READ currentMonthIndex   NOTIFY currentMonthIndexChanged  )
    Q_PROPERTY(int currentDaysIndex    READ currentDaysIndex    NOTIFY currentDaysIndexChanged   )
    Q_PROPERTY(int currentHoursIndex   READ currentHoursIndex   NOTIFY currentHoursIndexChanged  )
    Q_PROPERTY(int currentMinutesIndex READ currentMinutesIndex NOTIFY currentMinutesIndexChanged)

    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(int calendar READ calendar WRITE setCalendar NOTIFY calendarChanged)

    Q_PROPERTY(QDateTime minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(QDateTime maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)

public:

    enum CalendarTypes{
        CalendarGregorian = AsemanCalendarConverterCore::Gregorian,
        CalendarJalali = AsemanCalendarConverterCore::Jalali,
        CalendarHijri = AsemanCalendarConverterCore::Hijri
    };

    AsemanCalendarModel(QObject *parent = 0);
    virtual ~AsemanCalendarModel();

    QList<int> years() const;
    QList<int> months() const;
    QList<int> days() const;
    QList<int> hours() const;
    QList<int> minutes() const;

    int currentYearIndex() const;
    int currentMonthIndex() const;
    int currentDaysIndex() const;
    int currentHoursIndex() const;
    int currentMinutesIndex() const;

    void setDateTime(const QDateTime &dt);
    QDateTime dateTime() const;

    void setCalendar(int t);
    int calendar() const;

    void setMinimum(const QDateTime &dt);
    QDateTime minimum() const;

    void setMaximum(const QDateTime &dt);
    QDateTime maximum() const;

public Q_SLOTS:
    void setConvertDate(int yearIdx, int monthIdx, int dayIdx, int hourIdx, int minuteIdx);
    QString monthName(int month);

Q_SIGNALS:
    void yearsChanged();
    void monthsChanged();
    void daysChanged();
    void hoursChanged();
    void minutesChanged();
    void secondsChanged();
    void dateTimeChanged();
    void calendarChanged();
    void minimumChanged();
    void maximumChanged();

    void currentYearIndexChanged();
    void currentMonthIndexChanged();
    void currentDaysIndexChanged();
    void currentHoursIndexChanged();
    void currentMinutesIndexChanged();

private Q_SLOTS:
    void refreshLists();
    void refreshLists_prv();

private:
    AsemanCalendarModelPrivate *p;
};

typedef AsemanCalendarModel QAsemanCalendarModel;

#endif // ASEMANCALENDARMODEL_H
