#include "asemanquickcontrolitem.h"
#include "asemanquickstyleattachedproperty.h"

#include <QQuickItem>
#include <QDebug>

#define ASEMAN_READ_STYLE(PROPERTY) \
    auto parentObject = AsemanQuickStyleAttachedProperty::findParent(this); \
    auto res = PROPERTY; \
    while (!res.has_value() && parentObject) { \
        auto attached = qobject_cast<AsemanQuickStyleAttachedProperty*>(qmlAttachedPropertiesObject<AsemanQuickStyleProperty>(parentObject, false)); \
        if (attached && attached->PROPERTY.has_value()) { \
            res = attached->PROPERTY; \
            break; \
        } \
        parentObject = AsemanQuickStyleAttachedProperty::findParent(parentObject); \
    }

#define ASEMAN_WRITE_STYLE(PROPERTY, SIGNAL_NAME) \
    std::function<void(QObject *obj)> callback; \
    callback = [&callback](QObject *obj) { \
        for (auto c: obj->children()) { \
            auto attached = qobject_cast<AsemanQuickStyleAttachedProperty*>(qmlAttachedPropertiesObject<AsemanQuickStyleProperty>(c, false)); \
            if (!attached) { \
                callback(c); \
                continue; \
            } \
            if (!attached->PROPERTY.has_value()) { \
                Q_EMIT attached->SIGNAL_NAME(); \
                callback(c); \
            } \
        } \
    }; \
    callback(AsemanQuickStyleAttachedProperty::findParent(this));

QHash<QString, QHash<QString, QString>> AsemanQuickStyleAttachedProperty::mThemePaths;

AsemanQuickStyleAttachedProperty::AsemanQuickStyleAttachedProperty(QObject *parent)
    : QObject(parent)
{
    auto item = qobject_cast<QQuickItem*>(parent);
    if (item)
    {
        connect(item, &QQuickItem::parentChanged, this, [item](){
            std::function<void(QObject *obj)> callback;
            callback = [&callback](QObject *obj) {
                for (auto c: obj->children()) {
                    auto attached = qobject_cast<AsemanQuickStyleAttachedProperty*>(qmlAttachedPropertiesObject<AsemanQuickStyleProperty>(c, false));
                    if (!attached) {
                        callback(c);
                        continue;
                    }

                    attached->invokeAllSignals();
                }
            };
            callback(item);
        });
    }

    invokeAllSignals();
}

AsemanQuickStyleAttachedProperty::~AsemanQuickStyleAttachedProperty()
{

}

void AsemanQuickStyleAttachedProperty::invokeAllSignals()
{
    QMetaObject::invokeMethod(this, [this](){
        Q_EMIT primaryColorChanged();
        Q_EMIT primaryTextColorChanged();
        Q_EMIT accentColorChanged();
        Q_EMIT accentTextColorChanged();
        Q_EMIT foregroundColorChanged();
        Q_EMIT backgroundColorChanged();
        Q_EMIT baseColorChanged();
        Q_EMIT baseTextColorChanged();
        Q_EMIT generalFontFamiliesChanged();
        Q_EMIT styleNameChanged();
        Q_EMIT stylesSearchPathChanged();
    }, Qt::QueuedConnection);
}

QObject *AsemanQuickStyleAttachedProperty::findParent(const QObject *obj) const
{
    auto item = qobject_cast<const QQuickItem*>(obj);
    if (item && item->parentItem())
        return item->parentItem();

    return obj->parent();
}

QStringList AsemanQuickStyleAttachedProperty::stylesSearchPath() const
{
    ASEMAN_READ_STYLE(mStylesSearchPath);
    return res.value_or(QStringList());
}

void AsemanQuickStyleAttachedProperty::setStylesSearchPath(const QStringList &newStylesSearchPath)
{
    if (mStylesSearchPath == newStylesSearchPath)
        return;
    mStylesSearchPath = newStylesSearchPath;
    ASEMAN_WRITE_STYLE(mStylesSearchPath, stylesSearchPathChanged);
    Q_EMIT stylesSearchPathChanged();
}

QString AsemanQuickStyleAttachedProperty::getStylePath(const QStringList &searchPaths, const QString &styleName)
{
    const auto searchPaths_str = searchPaths.join('\n');
    if (mThemePaths.value(searchPaths_str).contains(styleName))
        return mThemePaths.value(searchPaths_str).value(styleName);

    QString selectedPath;
    for (const auto &path: searchPaths)
    {
        auto files = QDir(path).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        if (files.contains(styleName))
        {
            selectedPath = path;
            if (path.right(1) != '/')
                selectedPath += '/';
            selectedPath += styleName;
            break;
        }
    }
    if (selectedPath.left(2) == QStringLiteral(":/"))
        selectedPath = QStringLiteral("qrc") + selectedPath;

    mThemePaths[searchPaths_str][styleName] = selectedPath;
    return selectedPath;
}

QUrl AsemanQuickStyleAttachedProperty::styleUrl() const
{
    auto paths = stylesSearchPath();
    if (paths.isEmpty())
        paths = QStringList({":/AsemanQml/Controls/Beta/styles/"});

    auto name = styleName();
    if (name.isEmpty())
        name = "simple";

    return getStylePath(paths, name);
}

QString AsemanQuickStyleAttachedProperty::styleName() const
{
    ASEMAN_READ_STYLE(mStyleName);
    return res.value_or(QString());
}

void AsemanQuickStyleAttachedProperty::setStyleName(const QString &newStyleName)
{
    if (mStyleName == newStyleName)
        return;
    mStyleName = newStyleName;
    ASEMAN_WRITE_STYLE(mStyleName, styleNameChanged);
    Q_EMIT styleNameChanged();
}

QStringList AsemanQuickStyleAttachedProperty::generalFontFamilies() const
{
    ASEMAN_READ_STYLE(mGeneralFontFamilies);
    return res.value_or(QStringList());
}

void AsemanQuickStyleAttachedProperty::setGeneralFontFamilies(const QStringList &newGeneralFontFamilies)
{
    if (mGeneralFontFamilies == newGeneralFontFamilies)
        return;

    mGeneralFontFamilies = newGeneralFontFamilies;
    ASEMAN_WRITE_STYLE(mGeneralFontFamilies, generalFontFamiliesChanged);
    Q_EMIT generalFontFamiliesChanged();
}

QColor AsemanQuickStyleAttachedProperty::accentColor() const
{
    ASEMAN_READ_STYLE(mAccentColor);
    return res.value_or(QColor());
}

void AsemanQuickStyleAttachedProperty::setAccentColor(const QColor &newHighlightColor)
{
    if (mAccentColor == newHighlightColor)
        return;
    mAccentColor = newHighlightColor;
    ASEMAN_WRITE_STYLE(mAccentColor, accentColorChanged);
    Q_EMIT accentColorChanged();
}

QColor AsemanQuickStyleAttachedProperty::accentTextColor() const
{
    ASEMAN_READ_STYLE(mAccentTextColor);
    return res.value_or(QColor());
}

void AsemanQuickStyleAttachedProperty::setAccentTextColor(const QColor &newHighlightTextColor)
{
    if (mAccentTextColor == newHighlightTextColor)
        return;
    mAccentTextColor = newHighlightTextColor;
    ASEMAN_WRITE_STYLE(mAccentTextColor, accentTextColorChanged);
    Q_EMIT accentTextColorChanged();
}

QColor AsemanQuickStyleAttachedProperty::foregroundColor() const
{
    ASEMAN_READ_STYLE(mForegroundColor);
    return res.value_or(QColor());
}

void AsemanQuickStyleAttachedProperty::setForegroundColor(const QColor &newForegroundColor)
{
    if (mForegroundColor == newForegroundColor)
        return;
    mForegroundColor = newForegroundColor;
    ASEMAN_WRITE_STYLE(mForegroundColor, foregroundColorChanged);
    Q_EMIT foregroundColorChanged();
}

QColor AsemanQuickStyleAttachedProperty::backgroundColor() const
{
    ASEMAN_READ_STYLE(mBackgroundColor);
    return res.value_or(QColor());
}

void AsemanQuickStyleAttachedProperty::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (mBackgroundColor == newBackgroundColor)
        return;
    mBackgroundColor = newBackgroundColor;
    ASEMAN_WRITE_STYLE(mBackgroundColor, backgroundColorChanged);
    Q_EMIT backgroundColorChanged();
}

QColor AsemanQuickStyleAttachedProperty::primaryColor() const
{
    ASEMAN_READ_STYLE(mPrimaryColor);
    return res.value_or(QColor());
}

void AsemanQuickStyleAttachedProperty::setPrimaryColor(const QColor &newPrimaryColor)
{
    if (mPrimaryColor == newPrimaryColor)
        return;
    mPrimaryColor = newPrimaryColor;
    ASEMAN_WRITE_STYLE(mPrimaryColor, primaryColorChanged);
    Q_EMIT primaryColorChanged();
}

QColor AsemanQuickStyleAttachedProperty::primaryTextColor() const
{
    ASEMAN_READ_STYLE(mPrimaryTextColor);
    return res.value_or(QColor());
}

void AsemanQuickStyleAttachedProperty::setPrimaryTextColor(const QColor &newPrimaryTextColor)
{
    if (mPrimaryTextColor == newPrimaryTextColor)
        return;
    mPrimaryTextColor = newPrimaryTextColor;
    ASEMAN_WRITE_STYLE(mPrimaryTextColor, primaryTextColorChanged);
    Q_EMIT primaryTextColorChanged();
}

QColor AsemanQuickStyleAttachedProperty::baseColor() const
{
    ASEMAN_READ_STYLE(mBaseColor);
    return res.value_or(QColor());
}

void AsemanQuickStyleAttachedProperty::setBaseColor(const QColor &newBaseColor)
{
    if (mBaseColor == newBaseColor)
        return;
    mBaseColor = newBaseColor;
    ASEMAN_WRITE_STYLE(mBaseColor, baseColorChanged);
    Q_EMIT baseColorChanged();
}

QColor AsemanQuickStyleAttachedProperty::baseTextColor() const
{
    ASEMAN_READ_STYLE(mBaseTextColor);
    return res.value_or(QColor());
}

void AsemanQuickStyleAttachedProperty::setBaseTextColor(const QColor &newBaseTextColor)
{
    if (mBaseTextColor == newBaseTextColor)
        return;
    mBaseTextColor = newBaseTextColor;
    ASEMAN_WRITE_STYLE(mBaseTextColor, baseTextColorChanged);
    Q_EMIT baseTextColorChanged();
}

AsemanQuickStyleAttachedProperty *AsemanQuickStyleProperty::qmlAttachedProperties(QObject *object)
{
    return new AsemanQuickStyleAttachedProperty(object);
}
