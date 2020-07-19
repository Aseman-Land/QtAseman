#ifndef ASEMANOBJECTIVECLAYER_H
#define ASEMANOBJECTIVECLAYER_H

#include <QString>

class AsemanObjectiveCLayer
{
public:
    AsemanObjectiveCLayer();
    static qreal statusBarHeight();
    static qreal navigationBarHeight();
};

typedef AsemanObjectiveCLayer QAsemanObjectiveCLayer;

#endif // ASEMANOBJECTIVECLAYER_H
