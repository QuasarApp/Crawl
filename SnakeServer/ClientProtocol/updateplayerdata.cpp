#include "updateplayerdata.h"
#include "config.h"


namespace ClientProtocol {

UpdatePlayerData::UpdatePlayerData() {

}

SHA256 UpdatePlayerData::getToken() const {
    return token;
}

void UpdatePlayerData::setToken(const SHA256 &value) {
    token = value;
}

BaseNetworkObject *UpdatePlayerData::create() const {
    return new UpdatePlayerData();
}

NetworkClassSize UpdatePlayerData::classSize() const {
    return BaseNetworkObject::classSize() + getTypeSize(token);
}

QDataStream &UpdatePlayerData::writeToStream(QDataStream &stream) const {
    BaseNetworkObject::writeToStream(stream);
    stream << token;
    return stream;
}

QDataStream &UpdatePlayerData::readFromStream(QDataStream &stream) {
    BaseNetworkObject::readFromStream(stream);
    stream >> token;
    return stream;
}

bool UpdatePlayerData::isValid() const {
    return token.size() == 32 && BaseNetworkObject::isValid();
}

}
