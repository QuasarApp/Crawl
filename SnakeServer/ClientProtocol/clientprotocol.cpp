#include "clientprotocol.h"

#include <QDataStream>
#include <QVariantMap>
#include <networkobjects.h>
#include <streamers.h>

#define DEFAULT_GAME_PORT 7777

namespace ClientProtocol {


Header::Header() {
    reset();
}

bool Header::isValid() const {

    if (sizeof (*this) != 4) {
        return false;
    }

    switch (command) {
    case Ping: {

        if (type > 1 || size > 0)
            return false;

        return true;
    }

    case Item: {

        switch (type) {
        case Request: return size == 36; // key sha256 (32byte) + id item 4
        case Responke: return true;
        }

        return false;
    }

    case Login: {

        switch (type) {
        case Request: return size == 96; // key sha256 (32byte) + maxsize of name of gmail (64)
        case Responke: return isValidSize(NetworkClasses::Player, size);
        }

        return false;
    }

    case PlayerData: {

        switch (type) {
        case Request: return size == 32; // key sha256 (32byte)
        case Responke: return isValidSize(NetworkClasses::Player, size);
        }

        return false;
    }

    case ApplyData: {

        switch (type) {
        case Request: return isValidSize(NetworkClasses::Game, size);; // key sha256 (32byte) + maxsize of name of gmail (64)
        case Responke: return isValidSize(NetworkClasses::Player, size);
        }

        return false;
    }

    default: return false;
    }
}

void Header::reset() {
    size = 0;
    command = Undefined;
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

bool Package::parse(QVariantMap& res) const {
    if (!isValid())
        return false;

    res["command"] = hdr.command;
    res["type"] = hdr.type;
    res["sig"] = hdr.sig;

    switch (hdr.command) {
    case Ping: {
        if (hdr.type == Responke) {
            res["res"] = "Pong";
        } else {
            res["value"] = "Ping";
        }
        break;
    }

    case Item: {

        if (hdr.type == Responke) {

            QDataStream stream(data);
            if (!Streamers::read(stream, res)) {
                return false;
            }

        } else {
            res["token"] = data.left(32);
            res["id"] = data.right(4).toInt();
        }

        break;
    }

    case Login: {

        if (hdr.type == Responke) {

            QDataStream stream(data);

            if (!Streamers::read(stream, res)) {
                return false;
            }

        } else {
            QDataStream stream(data);
            QString gmail;
            QByteArray hash;

            stream >> gmail;
            stream >> hash;

            res["gmail"] = gmail;
            res["hash"] = hash;
        }
        break;
    }

    case PlayerData: {

        if (hdr.type == Responke) {

            QDataStream stream(data);
            if (!Streamers::read(stream, res)) {
                return false;
            }

        } else {
            QDataStream stream(data);
            QByteArray token;

            stream >> token;

            res["token"] = token;
        }
        break;
    }
    case ApplyData: {

        if (hdr.type == Responke) {

            if (data.size() != 1) {
                return false;
            }
            res["res"] = static_cast<bool>(data.at(0));

        } else {
            QDataStream stream(data);

            if (!Streamers::read(stream, res, NetworkClasses::Game)) {
                return false;
            }
        }
        break;
    }
    default:
        return false;

    }

    return true;
}


bool Package::create(const QVariantMap &map) {

    auto command = static_cast<unsigned char>(map.value("command", 0xff).toInt());
    auto type = static_cast<unsigned char>(map.value("type", 0xff).toInt());

    if (command == 0xff || type == 0xff) {
        return false;
    }

    switch (command) {
    case Ping: {
        break;
    }

    case Item: {

        if (type == Responke) {

            QDataStream stream(data);

            if (!Streamers::write(stream, map)) {
                return false;
            }

        } else {
            QDataStream stream(data);

            QByteArray hash = map.value("token", "").toByteArray();
            int id = map.value("id", 0).toInt();

            if (hash.size() != 32 || !id) {
                return false;
            }

            data.append(hash.data());
            data.append(reinterpret_cast<char*>(&id), sizeof (id));
        }

        break;

    }

    case Login: {

        if (type == Responke) {

            QDataStream stream(data);

            if (!Streamers::write(stream, map)) {
                return false;
            }

        } else {
            QDataStream stream(data);

            QByteArray hash = map.value("hash", "").toByteArray();
            QString gmail = map.value("gmail", "").toString();

            if (hash.size() != 32 || gmail.isEmpty()) {
                return false;
            }

            stream << gmail;
            stream << hash;
        }
        break;
    }

    case PlayerData: {

        if (type == Responke) {

            QDataStream stream(data);

            if (!Streamers::write(stream, map)) {
                return false;
            }

        } else {
            QDataStream stream(data);

            QByteArray token = map.value("token", "").toByteArray();

            stream << token;
        }
        break;
    }
    default: return false;

    }

    hdr.command = command;
    hdr.type = type;

    return isValid();
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

int getSize(NetworkClasses::Type type, bool isMax) {
    auto size = NetworkClasses::getSizeType(type);
    if (size) {
        return size;
    }

    if (type == NetworkClasses::String) {
        return 255;
    } else if (type == NetworkClasses::Variant) {
        return 16;
    }

    auto listPropertyes = networkObjects.value(type);
    size = 0;
    for (auto &&i : listPropertyes) {

        if (NetworkClasses::isArray(i)) {
            NetworkClasses::Type arrayType = static_cast<NetworkClasses::Type>(type & ~NetworkClasses::Array);

            auto sizeItem = NetworkClasses::getSizeType(arrayType);

            if (arrayType == NetworkClasses::String) {
                sizeItem = 255;
            } else if (arrayType == NetworkClasses::Variant) {
                sizeItem = 16;
            }

            size += sizeItem * ((isMax)? MAX_SIZE: MIN_SIZE);
        }

        size += getSize(i, isMax);
    }

    return size;
}

bool isStaticObject(NetworkClasses::Type type, int &max, int &min) {
    max = getSize(type);
    min = getSize(type, false);

    return max == min;
}

bool isValidSize(NetworkClasses::Type type, int size) {
    int max;
    int min;
    if (isStaticObject(type, max, min)) {
        return size == max;
    }

    return size <= max && size >= min;

}

}
