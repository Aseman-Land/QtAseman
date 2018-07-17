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

#ifndef ASEMANCALENDARCONVERTER_H
#define ASEMANCALENDARCONVERTER_H

#include <QObject>
#include <QStringList>
#include <QDateTime>

#include "asemancalendarconvertercore.h"

#include "asemancore_global.h"

class DateProperty;
class AsemanCalendarConverterPrivate;
class LIBQTASEMAN_CORE_EXPORT AsemanCalendarConverter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int calendar READ calendar WRITE setCalendar NOTIFY calendarChanged)

    Q_PROPERTY(QStringList calendarsID  READ calendarsID  NOTIFY fakeSignal)
    Q_PROPERTY(int         currentDays  READ currentDays  NOTIFY fakeSignal)
    Q_PROPERTY(int         currentYear  READ currentYear  NOTIFY fakeSignal)
    Q_PROPERTY(int         currentMonth READ currentMonth NOTIFY fakeSignal)
    Q_PROPERTY(int         currentDay   READ currentDay   NOTIFY fakeSignal)

public:
    AsemanCalendarConverter(QObject *parent = 0);
    virtual ~AsemanCalendarConverter();

    void setCalendar( int t );
    int calendar() const;

    QStringList calendarsID() const;

    static int currentDays();
    qint64 currentYear();
    int currentMonth();
    int currentDay();
    DateProperty convertDate( const QDate & date );

public Q_SLOTS:
    QString calendarName( int t );

    QString convertIntToStringDate(qint64 d );
    QString convertIntToFullStringDate(qint64 d );
    QString convertIntToNumStringDate(qint64 d );
    QString translateInt(qint64 d);
    QString convertIntToStringDate(qint64 d, const QString & format );
    QDate convertDateToGragorian( qint64 year, int month, int day );

    QString fromMSecSinceEpoch( qint64 t );
    QString convertDateTimeToString( const QDateTime & dt );
    QString convertDateTimeToString( const QDateTime & dt, const QString & format );
    QString convertDateTimeToLittleString( const QDate & dt );
    int daysOfMonth( qint64 year, int month );
    QString monthName( int month );

    QDateTime combineDateAndTime( const QDate & date, const QTime & time );

    int dateMonth( const QDate & date );
    int dateDay( const QDate & date );
    qint64 dateYear( const QDate & date );

    static QDate convertDaysToDate( int days );
    static int convertDateToDays( const QDate & date );

    QDateTime fromTime_t( uint sec );

Q_SIGNALS:
    void calendarChanged();
    void fakeSignal();

private:
    AsemanCalendarConverterPrivate *p;
};

#endif // ASEMANCALENDARCONVERTER_H
