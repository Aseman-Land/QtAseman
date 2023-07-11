#include "asemanquickstyleattachedproperty.h"
#include "asemanquickstyleditem.h"

#include <QQmlContext>
#include <QtQml>

QHash<QQmlEngine*, QHash<QString, QQmlComponent*>> AsemanQuickStyledItem::mStyleComponentObjects;

AsemanQuickStyledItem::AsemanQuickStyledItem(QQuickItem *parent)
    : QQuickItem(parent)
{
    mStyleItem = new AsemanQuickAbstractStyle(this);
}

AsemanQuickStyledItem::~AsemanQuickStyledItem()
{
}

QQmlComponent *AsemanQuickStyledItem::styleComponent() const
{
    return mStyleComponent;
}

void AsemanQuickStyledItem::setStyleComponent(QQmlComponent *newStyleComponent)
{
    if (mStyleComponent == newStyleComponent)
        return;

    mStyleComponent = newStyleComponent;
    setupStyleItem();
    Q_EMIT styleComponentChanged();
}

void AsemanQuickStyledItem::reposItems()
{
    if (mStyleItem)
    {
        mStyleItem->setX(0);
        mStyleItem->setY(0);
        mStyleItem->setWidth(mSourceItem? mSourceItem->width() : width());
        mStyleItem->setHeight(mSourceItem? mSourceItem->height() : height());
    }
}

void AsemanQuickStyledItem::reinitImplicitSizes()
{
    if (mStyleItem && mSourceItem)
    {
        mSourceItem->setImplicitWidth(mStyleItem->implicitWidth());
        mSourceItem->setImplicitHeight(mStyleItem->implicitHeight());
    }
}

void AsemanQuickStyledItem::reloadStyleTheme()
{
    if (mStyleFileName.isEmpty())
        return;
    if (!parentItem())
        return;

    auto attached = qobject_cast<AsemanQuickStyleAttachedProperty*>(qmlAttachedPropertiesObject<AsemanQuickStyleProperty>(this, true));

    auto url = attached->styleUrl();
    const auto path = url.toString() + '/' + mStyleFileName;
    if (path != mLastStylePath)
    {
        mLastStylePath = path;
        if (!url.isEmpty())
        {
            auto engine = qmlEngine(this);
            if (engine)
            {
                auto &component = mStyleComponentObjects[engine][path];
                if (!component)
                {
                    component = new QQmlComponent(engine, QUrl(path), engine);
                    connect(component, &QObject::destroyed, [engine, path](){
                        mStyleComponentObjects[engine].remove(path);
                        if (mStyleComponentObjects.value(engine).isEmpty())
                            mStyleComponentObjects.remove(engine);
                    });
                }
                if (component->isError())
                {
                    qDebug() << component->errorString().toStdString().c_str();
                    delete component;
                    component = nullptr;
                }
                else
                    setStyleComponent(component);
            }
        }
        else
            qmlWarning(this) << "Could not find style " << mStyleFileName;
    }
}

void AsemanQuickStyledItem::setupStyleItem()
{
    if (mStyleItem)
    {
        delete mStyleItem;
        mStyleItem = nullptr;
    }

    if (!mSourceItem)
        return;
    if (!mStyleComponent || !mStyleComponent->isReady())
        return;

    auto context = qmlContext(this);
    auto newContext = new QQmlContext(context, this);
    newContext->setContextProperty("control", mSourceItem);

    QVariantMap properties = {
        {"parent", QVariant::fromValue<QObject*>(this)}
    };

    auto obj = mStyleComponent->createWithInitialProperties(properties, newContext);
    mStyleItem = qobject_cast<AsemanQuickAbstractStyle*>(obj);
    if (mStyleItem)
    {
        connect(mStyleItem, &QQuickItem::implicitWidthChanged, this, &AsemanQuickStyledItem::reinitImplicitSizes);
        connect(mStyleItem, &QQuickItem::implicitHeightChanged, this, &AsemanQuickStyledItem::reinitImplicitSizes);
        reinitImplicitSizes();
        reposItems();
    }
    else
        delete obj;

    Q_EMIT styleItemChanged();
}

QQuickItem *AsemanQuickStyledItem::sourceItem() const
{
    return mSourceItem;
}

void AsemanQuickStyledItem::setSourceItem(QQuickItem *newSourceItem)
{
    if (mSourceItem == newSourceItem)
        return;
    if (mSourceItem)
    {
        disconnect(mSourceItem, &AsemanQuickStyledItem::widthChanged, this, &AsemanQuickStyledItem::reposItems);
        disconnect(mSourceItem, &AsemanQuickStyledItem::heightChanged, this, &AsemanQuickStyledItem::reposItems);
        disconnect(mSourceItem, &QQuickItem::parentChanged, this, &AsemanQuickStyledItem::reloadStyleTheme);
    }
    mSourceItem = newSourceItem;
    if (mSourceItem)
    {
        connect(mSourceItem, &AsemanQuickStyledItem::widthChanged, this, &AsemanQuickStyledItem::reposItems);
        connect(mSourceItem, &AsemanQuickStyledItem::heightChanged, this, &AsemanQuickStyledItem::reposItems);
        connect(mSourceItem, &QQuickItem::parentChanged, this, &AsemanQuickStyledItem::reloadStyleTheme);
        reposItems();
    }

    setupStyleItem();
    Q_EMIT sourceItemChanged();
}

AsemanQuickAbstractStyle *AsemanQuickStyledItem::styleItem() const
{
    return mStyleItem;
}

QString AsemanQuickStyledItem::styleFileName() const
{
    return mStyleFileName;
}

void AsemanQuickStyledItem::setStyleFileName(const QString &newStyleFileName)
{
    if (mStyleFileName == newStyleFileName)
        return;
    mStyleFileName = newStyleFileName;
    reloadStyleTheme();
    Q_EMIT styleFileNameChanged();
}
