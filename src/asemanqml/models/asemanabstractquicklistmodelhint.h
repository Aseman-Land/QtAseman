#ifndef ASEMANABSTRACTQUICKLISTMODELHINT_H
#define ASEMANABSTRACTQUICKLISTMODELHINT_H

#include <QObject>
#include <QVariant>

class AsemanAbstractQuickListModelHint : public QObject
{
    Q_OBJECT
    friend class AsemanQuickListModel;
    friend class AsemanQuickListModelSource;

public:
    AsemanAbstractQuickListModelHint(QObject *parent = Q_NULLPTR);
    virtual ~AsemanAbstractQuickListModelHint();

protected:
    virtual QVariantMap analyze(const QVariantMap &map) = 0;
    static QVariant getPathValue(QVariant data, const QString &path);
    static QVariant setPathValue(const QVariant &data, const QString &path, const QVariant &value);
    static QVariant deletePath(const QVariant &data, const QString &path);

private:
    static QVariant setPathValue(const QVariant &data, QStringList pathList, const QVariant &value);
    static QVariant deletePath(const QVariant &data, QStringList pathList);
};

#endif // ASEMANABSTRACTQUICKLISTMODELHINT_H
