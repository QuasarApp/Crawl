#include "login.h"
#include "config.h"

namespace ClientProtocol {

Login::Login() {

}

BaseNetworkObject *Login::create() const {
    return new Login();
}

NetworkClassSize Login::classSize() const {
    auto size = BaseNetworkObject::classSize();
    return size + getTypeSize(hashPass) + getTypeSize(gmail);
}

QDataStream &Login::writeToStream(QDataStream &stream) const {
    BaseNetworkObject::writeToStream(stream);
    stream << gmail;
    stream << hashPass;
    return stream;
}

QDataStream &Login::readFromStream(QDataStream &stream) {
    BaseNetworkObject::readFromStream(stream);
    stream >> gmail;
    stream >> hashPass;
    return stream;
}

bool Login::isValid() const {
    return  gmail.size() > 5 &&
            hashPass.size() == 32 &&
            BaseNetworkObject::isValid();
}

QString Login::getGmail() const {
    return gmail;
}

void Login::setGmail(const QString &value) {
    gmail = value;
}

SHA256 Login::getHashPass() const {
    return hashPass;
}

void Login::setHashPass(const SHA256 &value) {
    hashPass = value;
}
}
