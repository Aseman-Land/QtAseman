#ifndef ASEMANQUICKLISTMODELCAMELCASEHINT_H
#define ASEMANQUICKLISTMODELCAMELCASEHINT_H

#include <QObject>
#include <QJSValue>

#include "asemanabstractquicklistmodelhint.h"

class AsemanQuickListModelCamelCaseHint : public AsemanAbstractQuickListModelHint
{
    Q_OBJECT
    class Private;
    friend class AsemanQuickListModelSource;

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)

public:
    AsemanQuickListModelCamelCaseHint(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickListModelCamelCaseHint();

    void setPath(const QString &path);
    QString path() const;

Q_SIGNALS:
    void pathChanged();
    void changeRequest();

protected:
    virtual QVariantMap analyze(const QVariantMap &map);

private:
    QVariant toCamelCase(const QVariant &var);

private:
    Private *p;
};

#endif // ASEMANQUICKLISTMODELCAMELCASEHINT_H
