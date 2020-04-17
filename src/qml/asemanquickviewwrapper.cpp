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

#include "asemanquickviewwrapper.h"

AsemanQuickViewWrapper::AsemanQuickViewWrapper(AsemanQuickView *view, QObject *parent) :
    QObject(parent),
    mView(view)
{
    connect(mView, &AsemanQuickView::statusBarHeightChanged, this, &AsemanQuickViewWrapper::statusBarHeightChanged);
    connect(mView, &AsemanQuickView::navigationBarHeightChanged, this, &AsemanQuickViewWrapper::navigationBarHeightChanged);
    connect(mView, &AsemanQuickView::rootChanged, this, &AsemanQuickViewWrapper::rootChanged);
    connect(mView, &AsemanQuickView::focusedTextChanged, this, &AsemanQuickViewWrapper::focusedTextChanged);
    connect(mView, &AsemanQuickView::reverseScrollChanged, this, &AsemanQuickViewWrapper::reverseScrollChanged);
    connect(mView, &AsemanQuickView::fakeSignal, this, &AsemanQuickViewWrapper::fakeSignal);
    connect(mView, &AsemanQuickView::closeRequest, this, &AsemanQuickViewWrapper::closeRequest);
    connect(mView, &AsemanQuickView::destroyed, this, &AsemanQuickViewWrapper::viewDestroyed);
    connect(mView, &AsemanQuickView::offlineStoragePathChanged, this, &AsemanQuickViewWrapper::offlineStoragePathChanged);
}

AsemanQuickViewWrapper::~AsemanQuickViewWrapper()
{
}

void AsemanQuickViewWrapper::setReverseScroll(bool stt)
{
    mView->setReverseScroll(stt);
}

bool AsemanQuickViewWrapper::reverseScroll() const
{
    return mView->reverseScroll();
}

qreal AsemanQuickViewWrapper::statusBarHeight() const
{
    return mView->statusBarHeight();
}

qreal AsemanQuickViewWrapper::navigationBarHeight() const
{
    return mView->navigationBarHeight();
}

void AsemanQuickViewWrapper::setRoot(QObject *root)
{
    mView->setRoot(root);
}

QObject *AsemanQuickViewWrapper::root() const
{
    return mView->root();
}

void AsemanQuickViewWrapper::setFocusedText(QQuickItem *item)
{
    mView->setFocusedText(item);
}

QQuickItem *AsemanQuickViewWrapper::focusedText() const
{
    return mView->focusedText();
}

qreal AsemanQuickViewWrapper::flickVelocity() const
{
    return mView->flickVelocity();
}

QWindow *AsemanQuickViewWrapper::window() const
{
    return 0;
}

void AsemanQuickViewWrapper::setOfflineStoragePath(const QString &path)
{
    mView->setOfflineStoragePath(path);
}

QString AsemanQuickViewWrapper::offlineStoragePath() const
{
    return mView->offlineStoragePath();
}

void AsemanQuickViewWrapper::registerWindow(QQuickWindow *window)
{
    mView->registerWindow(window);
}

void AsemanQuickViewWrapper::discardFocusedText()
{
    mView->discardFocusedText();
}

void AsemanQuickViewWrapper::viewDestroyed()
{
    deleteLater();
}
