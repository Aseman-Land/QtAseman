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

#include "asemanglobaltranslations.h"

#include <QCoreApplication>
#include <QPointer>
#include <QSet>

class AsemanGlobalTranslations::Private
{
public:
    static QSet<AsemanGlobalTranslations*> objects;
};

QSet<AsemanGlobalTranslations*> AsemanGlobalTranslations::Private::objects;

AsemanGlobalTranslations::AsemanGlobalTranslations(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->objects.insert(this);
}

AsemanGlobalTranslations *AsemanGlobalTranslations::instance()
{
    static QPointer<AsemanGlobalTranslations> res;
    if (!res)
        res = new AsemanGlobalTranslations(QCoreApplication::instance());
    return res;
}

void AsemanGlobalTranslations::refresh()
{
    for (AsemanGlobalTranslations *o: Private::objects)
        Q_EMIT o->refreshed();
}

AsemanGlobalTranslations::~AsemanGlobalTranslations()
{
    p->objects.remove(this);
    delete p;
}
