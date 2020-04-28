#ifndef ASEMANQUICKLISTMODELFORMATHINT_H
#define ASEMANQUICKLISTMODELFORMATHINT_H

#include <QObject>
#include <QJSValue>

#include "asemanabstractquicklistmodelhint.h"

class AsemanQuickListModelFormatHint : public AsemanAbstractQuickListModelHint
{
    Q_OBJECT
    class Private;
    friend class AsemanQuickListModelSource;

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QJSValue method READ method WRITE setMethod NOTIFY methodChanged)

public:
    AsemanQuickListModelFormatHint(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickListModelFormatHint();

    void setPath(const QString &path);
    QString path() const;

    void setMethod(const QJSValue &method);
    QJSValue method() const;

Q_SIGNALS:
    void pathChanged();
    void methodChanged();
    void changeRequest();

protected:
    virtual QVariantMap analyze(const QVariantMap &map);

private:
    Private *p;
};

#endif // ASEMANQUICKLISTMODELFORMATHINT_H
