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

import QtQuick 2.9
import AsemanQml.Base 2.0
import AsemanQml.Models 2.0
import "."

Item {
    id: dt_chooser
    width: 400*Devices.density
    height: 150*Devices.density
    clip: true

    property color color: "transparent"
    property color textsColor
    property bool dateVisible: true
    property bool timeVisible: true

    property alias calendarType: model.calendar
    property alias date: model.dateTime

    CalendarModel {
        id: model
        onCurrentYearIndexChanged: year_list.positionViewAtIndex(currentYearIndex)
        onCurrentMonthIndexChanged: month_list.positionViewAtIndex(currentMonthIndex)
        onCurrentDaysIndexChanged: day_list.positionViewAtIndex(currentDaysIndex)
        onCurrentHoursIndexChanged: hour_list.positionViewAtIndex(currentHoursIndex)
        onCurrentMinutesIndexChanged: minute_list.positionViewAtIndex(currentMinutesIndex)

        Component.onCompleted: {
            year_list.positionViewAtIndex(currentYearIndex, true)
            month_list.positionViewAtIndex(currentMonthIndex, true)
            day_list.positionViewAtIndex(currentDaysIndex, true)
            hour_list.positionViewAtIndex(currentHoursIndex, true)
            minute_list.positionViewAtIndex(currentMinutesIndex, true)
        }

        function save() {
            save_timer.restart()
        }
    }

    Timer {
        id: save_timer
        interval: 800
        onTriggered: {
            model.setConvertDate(year_list.currentIndex,
                                 month_list.currentIndex,
                                 day_list.currentIndex,
                                 hour_list.currentIndex,
                                 minute_list.currentIndex)
        }
    }

    Row {
        id: row
        anchors.fill: parent

        SelectableList {
            id: year_list
            height: parent.height
            width: timeVisible? dt_chooser.width*3/14 : dt_chooser.width*75/225
            textsColor: dt_chooser.textsColor
            color: dt_chooser.color
            visible: dateVisible
            items: model.years
            onCurrentIndexChanged: model.save()
        }

        SelectableList {
            id: month_list
            height: parent.height
            width: timeVisible? dt_chooser.width*4/14 : dt_chooser.width*100/225
            textsColor: dt_chooser.textsColor
            color: dt_chooser.color
            visible: dateVisible
            nameMethodObject: model
            nameMethodFunction: "monthName"
            items: model.months
            onCurrentIndexChanged: model.save()
        }

        SelectableList {
            id: day_list
            height: parent.height
            width: timeVisible? dt_chooser.width*2/14 : dt_chooser.width*50/225
            textsColor: dt_chooser.textsColor
            color: dt_chooser.color
            visible: dateVisible
            items: model.days
            onCurrentIndexChanged: model.save()
        }

        Item {
            height: parent.height
            width: dt_chooser.width*1/14
            visible: dateVisible && timeVisible
        }

        SelectableList {
            id: hour_list
            height: parent.height
            width: dateVisible? dt_chooser.width*2/14 : dt_chooser.width*0.5
            textsColor: dt_chooser.textsColor
            color: dt_chooser.color
            visible: timeVisible
            nameMethodObject: row
            nameMethodFunction: "rightJustify"
            items: model.hours
            onCurrentIndexChanged: model.save()
        }

        SelectableList {
            id: minute_list
            height: parent.height
            width: dateVisible? dt_chooser.width*2/14 : dt_chooser.width*0.5
            textsColor: dt_chooser.textsColor
            color: dt_chooser.color
            visible: timeVisible
            nameMethodObject: row
            nameMethodFunction: "rightJustify"
            items: model.minutes
            onCurrentIndexChanged: model.save()
        }

        function rightJustify( str ) {
            var tempString = str.toString()
            while( tempString.length < 2 )
                tempString = "0" + tempString

            return tempString
        }
    }

    function getDate() {
        return model.dateTime
    }
}
