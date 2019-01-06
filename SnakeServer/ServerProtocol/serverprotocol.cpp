#include "serverprotocol.h"


ServerProtocol::Header::Header() {
    reset();
}

bool ServerProtocol::Header::isValid() const {

    if (sizeof (*this) != 1) {
        return false;
    }

    switch (command) {
    case ping: {

        if (type > 1)
            return false;

        return true;
    }

    default: return false;
    }
}

void ServerProtocol::Header::reset() {
    size = 0;
    command = undefined;
    type = Responke;
}

ServerProtocol::Package::Package() {
    reset();
}

bool ServerProtocol::Package::isValid() const {
    if (!hdr.isValid()) {
        return false;
    }

    return hdr.size == data.size();
}

QVariantMap ServerProtocol::Package::parse() const {
    if (!isValid())
        return QVariantMap();

    QVariantMap res;

    switch (hdr.command) {
    case ping: {
        if (hdr.type == Responke) {
            res["res"] = "Pong";
        } else {
            res["value"] = "Ping";
        }
        break;
    }

    default:
        return res;

    }

    return res;
}

QByteArray ServerProtocol::Package::toBytes() const {
    QByteArray res;
    res.append(reinterpret_cast<char*>(const_cast<Header*>(&hdr)),
               sizeof (hdr));

    res.append(data);
    return res;
}

void ServerProtocol::Package::reset() {
    hdr.reset();
    data.clear();
}

