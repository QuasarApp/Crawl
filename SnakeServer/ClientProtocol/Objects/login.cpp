#include "login.h"
#include "config.h"
#include "clientprotocol.h"

namespace ClientProtocol {

Login::Login() {
    _class = static_cast<quint8>(Command::Login);
}

BaseNetworkObject *Login::create() const {
    return new Login();
}

NetworkClassSize Login::classSize() const {
    auto size = BaseNetworkObject::classSize();
    return size + getTypeSize(hashRsaPass) + getTypeSize(gmail);
}

QDataStream &Login::writeToStream(QDataStream &stream) const {
    BaseNetworkObject::writeToStream(stream);
    stream << gmail;
    stream << hashRsaPass;
    return stream;
}

QDataStream &Login::readFromStream(QDataStream &stream) {
    BaseNetworkObject::readFromStream(stream);
    stream >> gmail;
    stream >> hashRsaPass;
    return stream;
}

bool Login::isValid() const {
    return  gmail.size() > 5 &&
            hashRsaPass.size() >= 32 &&
            hashRsaPass.size() <= 64 &&
            BaseNetworkObject::isValid();
}

QString Login::getGmail() const {
    return gmail;
}

void Login::setGmail(const QString &value) {
    gmail = value;
}

QByteArray Login::getHashPass() const {
    return hashRsaPass;
}

void Login::setHashPass(const QByteArray &value) {
    hashRsaPass = value;
}
}
