#include "asemanrefresherobject.h"

AsemanRefresherObject::AsemanRefresherObject(QObject *parent)
    : QObject(parent)
{
    mDelayTimer = new QTimer(this);
    mDelayTimer->setSingleShot(true);

    connect(mDelayTimer, &QTimer::timeout, this, [this](){
        mRefreshing = true;
        Q_EMIT refreshingChanged();
        Q_EMIT activeChanged();
    });
}

AsemanRefresherObject::~AsemanRefresherObject()
{
}

bool AsemanRefresherObject::refreshing() const
{
    return mRefreshing;
}

bool AsemanRefresherObject::active() const
{
    return mDelayTimer->isActive() || mRefreshing;
}

void AsemanRefresherObject::setRefreshing(bool state)
{
    if (!state)
    {
        mDelayTimer->stop();
        if (mRefreshing)
            mInitialized = true;

        mRefreshing = false;
        Q_EMIT refreshingChanged();
    }
    else if (!mDelay || !mInitialized)
    {
        mDelayTimer->stop();
        mRefreshing = true;
        Q_EMIT refreshingChanged();
    }
    else
    {
        if (!mDelayTimer->isActive())
            mDelayTimer->start(mDelay);
    }
    Q_EMIT activeChanged();
}

qint32 AsemanRefresherObject::delay() const
{
    return mDelay;
}

bool AsemanRefresherObject::forceActiveOnInitialize() const
{
    return mForceActiveOnInitialize;
}

void AsemanRefresherObject::setForceActiveOnInitialize(bool newForceActiveOnInitialize)
{
    mForceActiveOnInitialize = newForceActiveOnInitialize;
    mInitialized = false;
}

void AsemanRefresherObject::setDelay(qint32 newDelay)
{
    if (mDelay == newDelay)
        return;

    mDelay = newDelay;
    if (mDelayTimer->isActive())
    {
        mDelayTimer->stop();
        if (mDelay)
            mDelayTimer->start(mDelay);
        else
        {
            mRefreshing = true;
            Q_EMIT refreshingChanged();
        }
    }

    Q_EMIT delayChanged();
}
