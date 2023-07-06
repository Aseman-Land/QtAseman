#ifndef ASEMANQUICKSTYLEDITEM_H
#define ASEMANQUICKSTYLEDITEM_H

#include <QQuickItem>
#include <QQmlComponent>
#include <QPointer>
#include <QUrl>

#include "asemanquickabstractstyle.h"

class AsemanQuickStyledItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *sourceItem READ sourceItem WRITE setSourceItem NOTIFY sourceItemChanged)
    Q_PROPERTY(QQmlComponent *styleComponent READ styleComponent WRITE setStyleComponent NOTIFY styleComponentChanged)
    Q_PROPERTY(QString styleFileName READ styleFileName WRITE setStyleFileName NOTIFY styleFileNameChanged)
    Q_PROPERTY(AsemanQuickAbstractStyle *styleItem READ styleItem NOTIFY styleItemChanged)

public:
    AsemanQuickStyledItem(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickStyledItem();

    QQmlComponent *styleComponent() const;
    void setStyleComponent(QQmlComponent *newStyleComponent);

    QString styleFileName() const;
    void setStyleFileName(const QString &newStyleFileName);

    AsemanQuickAbstractStyle *styleItem() const;

    QQuickItem *sourceItem() const;
    void setSourceItem(QQuickItem *newSourceItem);

Q_SIGNALS:
    void styleComponentChanged();
    void styleFileNameChanged();
    void styleItemChanged();
    void sourceItemChanged();

protected:
    void reposItems();
    void reinitImplicitSizes();
    void reloadStyleTheme();
    void setupStyleItem();

private:
    QPointer<QQuickItem> mSourceItem;
    QPointer<QQmlComponent> mStyleComponent;
    QString mStyleFileName;
    AsemanQuickAbstractStyle *mStyleItem = nullptr;
    QString mLastStylePath;

    static QHash<QQmlEngine*, QHash<QString, QQmlComponent*>> mStyleComponentObjects;
};

#endif // ASEMANQUICKSTYLEDITEM_H
