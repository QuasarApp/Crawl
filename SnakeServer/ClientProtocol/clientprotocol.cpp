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

    if (sizeof (*this) != 8) {
        return false;
    }

    return isValidSize(static_cast<NetworkClasses::Type>(command) , size);

//    switch (command) {
//    case Ping: {

//        if (type > 1 || size > 0)
//            return false;

//        return true;
//    }

//    case Item: {

//        switch (type) {
//        case Request: return size == 36; // key sha256 (32byte) + id item 4
//        case Responke: return true;
//        }

//        return false;
//    }

//    case Login: {

//        switch (type) {
//        case Request: return size > 36; // key sha256 (32byte) + 4 size array + maxsize of name of gmail (64)
//        case Responke: return isValidSize(NetworkClasses::Player, size);
//        }

//        return false;
//    }

//    case PlayerData: {

//        switch (type) {
//        case Request: return size == 36; // key sha256 (32byte + size of array)
//        case Responke: return isValidSize(NetworkClasses::Player, size);
//        }

//        return false;
//    }

//    case SaveData: {

//        switch (type) {
//        case Request: return isValidSize(NetworkClasses::Game, size);; // key sha256 (32byte) + maxsize of name of gmail (64)
//        case Responke: return isValidSize(NetworkClasses::Player, size);
//        }

//        return false;
//    }

//    default: return false;
//    }
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

    return hdr.size == static_cast<unsigned int> (data.size());
}

bool Package::parse(QVariantMap& res) const {
    if (!isValid())
        return false;

    res["command"] = hdr.command;
    res["type"] = hdr.type;
    res["sig"] = hdr.sig;

    QDataStream stream(data);

    if (!Streamers::read(stream, res, static_cast<NetworkClasses::Type>(hdr.command))) {
        return false;
    }

    return true;
}


bool Package::create(const QVariantMap &map, Type type) {

    auto command = static_cast<NetworkClasses::Type>(
                map.value("command", NetworkClasses::Undefined).toInt());

    if (!(command & NetworkClasses::CustomType) || type == Type::Undefined) {
        return false;
    }

    QDataStream stream(&data, QIODevice::ReadWrite);

    if (!Streamers::write(stream, map)) {
        return false;
    }

    hdr.command = command;
    hdr.type = type;
    hdr.size = static_cast<unsigned int>(data.size());

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

unsigned int getSize(NetworkClasses::Type type, bool isMax) {
    auto size = NetworkClasses::getSizeType(type);
    if (size) {
        return size;
    }

    if (type == NetworkClasses::String) {
        return (isMax)? 255: 5;
    } else if (type == NetworkClasses::Variant) {
        return (isMax)? 16 : 6;
    }

    if (NetworkClasses::isArray(type)) {
        NetworkClasses::Type arrayType = static_cast<NetworkClasses::Type>(type & ~NetworkClasses::Array);

        auto sizeItem = NetworkClasses::getSizeType(arrayType);

        if (arrayType == NetworkClasses::String) {
            sizeItem = (isMax)? 255: 5;
        } else if (arrayType == NetworkClasses::Variant) {
            sizeItem = (isMax)? 16 : 6;
        }

        constexpr int description = sizeof(int);

        size += description + sizeItem * ((isMax)? MAX_SIZE: MIN_SIZE);
        return size;
    }

    if (type & NetworkClasses::CustomType) {
        constexpr auto baseSize = sizeof (short);
        size += baseSize;
    }

    auto listPropertyes = networkObjects.value(type);
    for (auto &&i : listPropertyes) {
        size += getSize(i, isMax);
    }

    return size;
}

bool isStaticObject(NetworkClasses::Type type, unsigned int &max, unsigned int &min) {
    max = getSize(type, true);
    min = getSize(type);

    return max == min;
}

bool isValidSize(NetworkClasses::Type type, unsigned int size) {

    if (type == NetworkClasses::Undefined) {
        return false;
    }

    unsigned int max;
    unsigned int min;
    if (isStaticObject(type, max, min)) {
        return size == max;
    }

    return size <= max && size >= min;

}

}
