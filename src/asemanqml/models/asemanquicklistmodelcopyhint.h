#ifndef ASEMANQUICKLISTMODELCOPYHINT_H
#define ASEMANQUICKLISTMODELCOPYHINT_H

#include <QObject>
#include <QJSValue>

#include "asemanabstractquicklistmodelhint.h"

class AsemanQuickListModelCopyHint : public AsemanAbstractQuickListModelHint
{
    Q_OBJECT
    class Private;
    friend class AsemanQuickListModelSource;

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString targetPath READ targetPath WRITE setTargetPath NOTIFY targetPathChanged)
    Q_PROPERTY(QJSValue method READ method WRITE setMethod NOTIFY methodChanged)

public:
    AsemanQuickListModelCopyHint(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickListModelCopyHint();

    void setPath(const QString &path);
    QString path() const;

    void setTargetPath(const QString &targetPath);
    QString targetPath() const;

    void setMethod(const QJSValue &method);
    QJSValue method() const;

Q_SIGNALS:
    void pathChanged();
    void methodChanged();
    void changeRequest();
    void targetPathChanged();

protected:
    virtual QVariantMap analyze(const QVariantMap &map);

private:
    Private *p;
};

#endif // ASEMANQUICKLISTMODELCOPYHINT_H
