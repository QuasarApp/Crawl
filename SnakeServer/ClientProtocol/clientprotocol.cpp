#include "clientprotocol.h"


#include <QVariantMap>
#include <typeinfo>

#define DEFAULT_GAME_PORT 7777

namespace ClientProtocol {


Header::Header() {
    reset();
}

bool Header::isValid() const {

    if (sizeof (*this) != 2) {
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
        case Responke: return size < (snakeSize + sizeof (Class));
        }

        return false;
    }

    case Login: {

        switch (type) {
        case Request: return size == 96; // key sha256 (32byte) + maxsize of name of gmail (64)
        case Responke: return size < MAX_SIZE_PLAYER && size > MIN_SIZE_PLAYER;
        }

        return false;
    }

    case PlayerData: {

        switch (type) {
        case Request: return size == 96; // key sha256 (32byte) + maxsize of name of gmail (64)
        case Responke: return size < MAX_SIZE_PLAYER && size > MIN_SIZE_PLAYER;
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
            unsigned char type;
            stream >> type;

            switch (type) {
            case SnakeData:{
                if (!SnakeItem::read(stream, res)) {
                    return false;
                }
                break;
            }

            default: break;

            }
        } else {
            res["hash"] = data.left(32);
            res["id"] = data.right(4).toInt();
        }

        break;
    }

    case Login: {

        if (hdr.type == Responke) {

            QDataStream stream(data);

            if (!Player::read(stream, res)) {
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
            if (!Player::read(stream, res)) {
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
            auto cls = static_cast<unsigned char>(map.value("class", 0xff).toInt());
            stream << static_cast<unsigned char>(cls);

            switch (cls) {
            case SnakeData:{
                if (!SnakeItem::write(stream, map)) {
                    return false;
                }

                break;
            }
            default: return false;

            }
        } else {
            QDataStream stream(data);

            QByteArray hash = map.value("hash", "").toByteArray();
            int id = static_cast<Class>(map.value("id", 0).toInt());

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

            if (!Player::write(stream, map)) {
                return false;
            }

        } else {
            QDataStream stream(data);

            QByteArray hash = map.value("hash", "").toByteArray();
            QString gmail = map.value("id", "").toString();

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

            if (!Player::write(stream, map)) {
                return false;
            }

        } else {
            QDataStream stream(data);

            QByteArray hash = map.value("hash", "").toByteArray();
            QString gmail = map.value("id", "").toString();

            if (hash.size() != 32 || gmail.isEmpty()) {
                return false;
            }

            stream << gmail;
            stream << hash;
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

}
