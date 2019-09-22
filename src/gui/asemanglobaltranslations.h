/*
    Copyright (C) 2019 Aseman Team
    http://aseman.io

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANGLOBALTRANSLATIONS_H
#define ASEMANGLOBALTRANSLATIONS_H

#include <QObject>

#include "asemangui_global.h"

class LIBQTASEMAN_GUI_EXPORT AsemanGlobalTranslations : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString refresher READ refresher NOTIFY refreshed)

    class Private;
    friend class AsemanTranslationManager;

public:
    AsemanGlobalTranslations(QObject *parent = Q_NULLPTR);
    virtual ~AsemanGlobalTranslations();

    QString refresher() const { return QString(); }

    static AsemanGlobalTranslations *instance();

Q_SIGNALS:
    void refreshed();

private:
    static void refresh();

private:
    Private *p;
};

#endif // ASEMANGLOBALTRANSLATIONS_H
