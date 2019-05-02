#include "item.h"
#include "factorynetobjects.h"
#include <exception>

int Item::getId() const {
    return id;
}

void Item::setId(int value) {
    id = value;
}

Item::Item() {

}

Item::Item(const ClientProtocol::Package &other) {
    hdr = other.hdr;
    data = other.data;
    ClientProtocol::BaseNetworkObject base;
    base.fromBytes(data);
    id = base.id();
}

Item::Item(const ClientProtocol::BaseNetworkObject *obj) {
    if (!create(obj, ClientProtocol::Type::Stream)) {
        throw "Error create Item from BaseNetworkObject!";
    }

    id = obj->id();
}

Item::Item(ClientProtocol::Command cmd, const QByteArray &data) {
    if (!create(cmd, ClientProtocol::Type::Stream, data)) {
        throw std::runtime_error("Error create Item from BaseNetworkObject!");
    }

    ClientProtocol::BaseNetworkObject base;
    base.fromBytes(data);
    id = base.id();
}

Item::~Item() {

}

ClientProtocol::Command Item::cmd() const {
    return static_cast<ClientProtocol::Command>(hdr.command);
}

const QByteArray &Item::dataArray() const {
    return data;
}

bool Item::isValid() const {
    return ClientProtocol::FactoryNetObjects::isRegisteredType(hdr.type)
            && Package::isValid();
}
