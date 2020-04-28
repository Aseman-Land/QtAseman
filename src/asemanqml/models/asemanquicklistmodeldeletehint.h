#ifndef ASEMANQUICKLISTMODELDELETEHINT_H
#define ASEMANQUICKLISTMODELDELETEHINT_H

#include <QObject>
#include <QJSValue>

#include "asemanabstractquicklistmodelhint.h"

class AsemanQuickListModelDeleteHint : public AsemanAbstractQuickListModelHint
{
    Q_OBJECT
    class Private;
    friend class AsemanQuickListModelSource;

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)

public:
    AsemanQuickListModelDeleteHint(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickListModelDeleteHint();

    void setPath(const QString &path);
    QString path() const;

Q_SIGNALS:
    void pathChanged();
    void changeRequest();

protected:
    virtual QVariantMap analyze(const QVariantMap &map);

private:
    Private *p;
};

#endif // ASEMANQUICKLISTMODELDELETEHINT_H
