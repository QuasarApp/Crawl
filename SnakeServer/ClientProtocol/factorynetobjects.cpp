#include "factorynetobjects.h"
#include "clientprotocol.h"

QVariantMap ClientProtocol::FactoryNetObjects::build(
        ClientProtocol::NetworkClasses::Type type) {

    auto obj = ClientProtocol::networkObjects.value(type);
    QVariantMap res;

    res ["command"] = type;
    res ["id"] = -1;

    for (auto &&i: obj.keys()) {
        res[i] = "";
    }

    return res;
}

