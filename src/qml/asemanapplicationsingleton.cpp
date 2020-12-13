#include "asemanapplicationsingleton.h"

class AsemanApplicationSingletonPrivate
{
public:
};

AsemanApplicationSingleton::AsemanApplicationSingleton(QQmlEngine *engine) :
    AsemanApplicationItem(engine)
{
    p = new AsemanApplicationSingletonPrivate;
}

AsemanApplicationSingleton::~AsemanApplicationSingleton()
{
    delete p;
}
