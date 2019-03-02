#ifndef RANDOMOBJECTFACTORY_H
#define RANDOMOBJECTFACTORY_H
#include <networkobjects.h>

class RandomObjectFactory
{
public:
    RandomObjectFactory() = delete;
    static QVariantMap build(ClientProtocol::NetworkClasses::Type);
};

#endif // RANDOMOBJECTFACTORY_H
