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

#include "asemantranslationmanager.h"
#include "asemantools.h"

#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include <QDebug>

class AsemanTranslationManager::Private
{
public:
    QTranslator *translator;
    QUrl sourceDirectory;
    QString localeName;
    QString fileName;
    QString delimiters;
};

AsemanTranslationManager::AsemanTranslationManager(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->translator = 0;
}

void AsemanTranslationManager::setSourceDirectory(const QUrl &sourceDirectory)
{
    if(p->sourceDirectory == sourceDirectory)
        return;

    p->sourceDirectory = sourceDirectory;
    refresh();
    Q_EMIT sourceDirectoryChanged();
}

QUrl AsemanTranslationManager::sourceDirectory() const
{
    return p->sourceDirectory;
}

void AsemanTranslationManager::setLocaleName(const QString &localeName)
{
    if(p->localeName == localeName)
        return;

    p->localeName = localeName;
    refresh();
    Q_EMIT localeNameChanged();
}

QString AsemanTranslationManager::localeName() const
{
    return p->localeName;
}

void AsemanTranslationManager::setFileName(const QString &fileName)
{
    if(p->fileName == fileName)
        return;

    p->fileName = fileName;
    refresh();
    Q_EMIT fileNameChanged();
}

QString AsemanTranslationManager::fileName() const
{
    return p->fileName;
}

void AsemanTranslationManager::setDelimiters(const QString &delimiters)
{
    if(p->delimiters == delimiters)
        return;

    p->delimiters = delimiters;
    refresh();
    Q_EMIT delimitersChanged();
}

QString AsemanTranslationManager::delimiters() const
{
    return p->delimiters;
}

int AsemanTranslationManager::textDirection() const
{
    return QLocale(p->localeName).textDirection();
}

QMap<QString, QVariant> AsemanTranslationManager::translations() const
{
    QMap<QString, QVariant> res;
    QString path = AsemanTools::urlToLocalPath(p->sourceDirectory);

    QRegExp rx(p->fileName + p->delimiters + QStringLiteral("(\\w+)\\.qm"));
    QStringList files = QDir(path).entryList(QStringList()<<QStringLiteral("*.qm"), QDir::Files);
    for(const QString &file: files)
    {
        int pos = rx.indexIn(file);
        if (pos < 0)
            continue;

        QString cap = rx.cap(1);
        res[cap] = QLocale(cap).nativeLanguageName();
    }

    return res;
}

void AsemanTranslationManager::refresh()
{
    if(p->sourceDirectory.isEmpty() || p->fileName.isEmpty() || p->delimiters.isEmpty() || p->localeName.isEmpty())
        return;

    QString path = AsemanTools::urlToLocalPath(p->sourceDirectory);
    if(p->translator)
    {
        QCoreApplication::removeTranslator(p->translator);
        delete p->translator;
    }

    p->translator = new QTranslator(this);
    p->translator->load( QLocale(p->localeName), p->fileName, p->delimiters, path);

    QCoreApplication::installTranslator(p->translator);
    Q_EMIT refreshed();
    Q_EMIT textDirectionChanged();
    Q_EMIT translationsChanged();
}

AsemanTranslationManager::~AsemanTranslationManager()
{
    if(p->translator)
        QCoreApplication::removeTranslator(p->translator);

    delete p;
}
