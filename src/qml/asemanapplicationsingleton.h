#ifndef ASEMANAPPLICATIONSINGLETON_H
#define ASEMANAPPLICATIONSINGLETON_H

#include "asemanapplicationitem.h"

class AsemanApplicationSingletonPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanApplicationSingleton : public AsemanApplicationItem
{
    Q_OBJECT
public:
    AsemanApplicationSingleton(QQmlEngine *engine);
    virtual ~AsemanApplicationSingleton();

private:
    AsemanApplicationSingletonPrivate *p;
};

typedef AsemanApplicationSingleton QAsemanApplicationSingleton;

#endif // ASEMANAPPLICATIONSINGLETON_H
