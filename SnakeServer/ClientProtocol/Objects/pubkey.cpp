#include "pubkey.h"
#include "clientprotocol.h"

namespace ClientProtocol {

PubKey::PubKey() {
    _class = static_cast<quint8>(Command::PubKey);
}

QRSAEncryption::Rsa PubKey::getTypeKey() const {
    return typeKey;
}

void PubKey::setTypeKey(const QRSAEncryption::Rsa &value) {
    typeKey = value;
}

QByteArray PubKey::getKey() const {
    return key;
}

void PubKey::setKey(const QByteArray &value) {
    key = value;
}

BaseNetworkObject *PubKey::create() const {
    return new PubKey();
}

NetworkClassSize PubKey::classSize() const {
    return BaseNetworkObject::classSize() +
            QRSAEncryption::getBytesSize(typeKey) +
            static_cast<unsigned int>(sizeof (int)) +
            getTypeSize(typeKey);
}

QDataStream &PubKey::writeToStream(QDataStream &stream) const {
    BaseNetworkObject::writeToStream(stream);
    stream << int(typeKey);
    stream << key;
    return stream;
}

QDataStream &PubKey::readFromStream(QDataStream &stream) {
    BaseNetworkObject::readFromStream(stream);
    int _typeKey;
    stream >> _typeKey;
    typeKey = static_cast<QRSAEncryption::Rsa>(_typeKey);
    stream >> key;
    return stream;
}

bool PubKey::isValid() const {
    return static_cast<quint32>(key.size()) == QRSAEncryption::getBytesSize(typeKey)
            && BaseNetworkObject::isValid();
}

}
