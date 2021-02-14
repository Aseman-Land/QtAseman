#ifndef ASEMANOBJECTIVECLAYER_H
#define ASEMANOBJECTIVECLAYER_H

#include <QString>
#include <QVariantList>

#include <functional>

class AsemanObjectiveCLayer
{
public:
    AsemanObjectiveCLayer();
    static qreal statusBarHeight();
    static qreal navigationBarHeight();
    static bool saveToCameraRoll(const QString &filePath);
    static void getContactList(std::function<void(const QVariantList &res)> asyncCallback = Q_NULLPTR);
};

typedef AsemanObjectiveCLayer QAsemanObjectiveCLayer;

#endif // ASEMANOBJECTIVECLAYER_H
