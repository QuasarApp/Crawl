#include "factorynetobjects.h"
#include "clientprotocol.h"

namespace ClientProtocol {

QMap<quint8, BaseNetworkObject*> map;
QMap<quint8, NetworkClassSize> types_sizes;

BaseNetworkObject *FactoryNetObjects::build(quint8 type) {
    if (!map.contains(type)) {
        return nullptr;
    }

    return map.value(type)->create();
}

NetworkClassSize FactoryNetObjects::getSize(quint8 type) {
    return types_sizes.value(type, 0);
}

bool FactoryNetObjects::isRegisteredType(quint8 type) {
    return map.contains(type);
}

bool FactoryNetObjects::isInited() {
    return map.size();
}

}
