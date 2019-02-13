#include "clientprotocol.h"


#include <QVariantMap>

#define DEFAULT_GAME_PORT 7777

namespace ClientProtocol {


Header::Header() {
    reset();
}

bool Header::isValid() const {

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

void Header::reset() {
    size = 0;
    command = undefined;
    type = Responke;
}

Package::Package() {
    reset();
}

bool Package::isValid() const {
    if (!hdr.isValid()) {
        return false;
    }

    return hdr.size == data.size();
}

QVariantMap Package::parse() const {
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

QByteArray Package::toBytes() const {
    QByteArray res;
    res.append(reinterpret_cast<char*>(const_cast<Header*>(&hdr)),
               sizeof (hdr));

    res.append(data);
    return res;
}

void Package::reset() {
    hdr.reset();
    data.clear();
}

}
