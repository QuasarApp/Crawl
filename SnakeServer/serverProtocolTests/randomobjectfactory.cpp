#include "randomobjectfactory.h"
#include "networkobjects.h"
#include <clientprotocol.h>

QVariantMap RandomObjectFactory::build(ClientProtocol::NetworkClasses::Type type) {
    auto obj = ClientProtocol::networkObjects.value(type);
    QVariantMap res;

    for (auto &&i: obj.keys()) {
        auto size = ClientProtocol::getSize(obj.value(i));
        QByteArray array;
        array.append(size, 'c');
        res[i] = array;
    }

    return res;
}
