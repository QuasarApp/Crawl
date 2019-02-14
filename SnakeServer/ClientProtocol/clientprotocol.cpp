#include "clientprotocol.h"


#include <QVariantMap>
#include <typeinfo>
#include "snakeitem.h"
#include "player.h"

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
    case ping: {

        if (type > 1 || size > 0)
            return false;

        return true;
    }

    case item: {

        switch (type) {
        case Request: return size == 36; // key sha256 (32byte) + id item 4
        case Responke: return size < (snakeSize + sizeof (Class));
        }

        return false;
    }

    case login: {

        switch (type) {
        case Request: return size == 96; // key sha256 (32byte) + maxsize of name of gmail (64)
        case Responke: return size < MAX_SIZE_PLAYER && size > MIN_SIZE_PLAYER;
        }

        return false;
    }

    case playerData: {

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

    res["command"] = hdr.command;
    res["type"] = hdr.type;
    res["status"] = true;

    switch (hdr.command) {
    case ping: {
        if (hdr.type == Responke) {
            res["res"] = "Pong";
        } else {
            res["value"] = "Ping";
        }
        break;
    }

    case item: {

        if (hdr.type == Responke) {

            QDataStream stream(data);
            unsigned char type;
            stream >> type;

            switch (type) {
            case SnakeData:{
                if (!SnakeItem::read(stream, res)) {
                    res["status"] = false;
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

    case login: {

        if (hdr.type == Responke) {

            QDataStream stream(data);

            if (!Player::read(stream, res)) {
                res["status"] = false;
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

    case playerData: {

        if (hdr.type == Responke) {

            QDataStream stream(data);
            if (!Player::read(stream, res)) {
                res["status"] = false;
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
