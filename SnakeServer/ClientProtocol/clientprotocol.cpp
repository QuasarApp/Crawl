#include "clientprotocol.h"
#include "gamedata.h"
#include "getitem.h"
#include "login.h"
#include "player.h"
#include "updateplayerdata.h"

#include <QDataStream>
#include <QVariantMap>
#include <factorynetobjects.h>

#define DEFAULT_GAME_PORT 7777

namespace ClientProtocol {


Header::Header() {
    reset();
}

bool Header::isValid() const {

    if (sizeof (*this) != 4) {
        return false;
    }

    if (static_cast<Command>(command) == Command::Undefined) {
        return false;
    }

    if (static_cast<Type>(type) == Type::Undefined) {
        return false;
    }

    return isValidSize(command, size);
}

void Header::reset() {
    size = 0;
    command = static_cast<quint8>(Command::Undefined);
    type = static_cast<quint8>(Type::Responke);
}

Package::Package() {
    reset();
}

bool Package::isValid() const {
    if (!hdr.isValid()) {
        return false;
    }

    if (data.size() && hdr.command != data.at(0)) {
        return false;
    }

    return hdr.size == static_cast<unsigned int> (data.size());
}

BaseNetworkObject* Package::parse() const {
    if (!isValid())
        return nullptr;

    auto obj = FactoryNetObjects::build(hdr.command);

    if (!obj) {
        return nullptr;
    }

    QDataStream stream(data);
    obj->readFromStream(stream);

    return obj;
}


bool Package::create(const BaseNetworkObject *obj, Type type) {

    if (!obj) {
        return false;
    }

    auto command = obj->getClass();

    if (command < 0) {
        return false;
    }

    QDataStream stream(&data, QIODevice::ReadWrite);
    obj->writeToStream(stream);

    hdr.command = static_cast<quint8>(command);
    hdr.type = static_cast<quint8>(type);
    hdr.size = static_cast<unsigned short>(data.size());

    return isValid();
}

bool Package::create(Command cmd, Type type) {


    if (cmd == Command::Undefined) {
        return false;
    }

    hdr.command = static_cast<quint8>(cmd);
    hdr.type = static_cast<quint8>(type);
    hdr.size = static_cast<unsigned short>(data.size());

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

bool isValidSize(quint8 type, unsigned int size) {

    if (!FactoryNetObjects::isInited()) {
        return false;
    }

    if (!FactoryNetObjects::isRegisteredType(type)) {
        return size == 0;
    }

    return FactoryNetObjects::getSize(type).isValid(size);
}

bool initClientProtockol() {
    if (!FactoryNetObjects::regType<Login>(
                static_cast<quint8>(Command::Login))) {
        return false;
    }

    if (!FactoryNetObjects::regType<UpdatePlayerData>(
                static_cast<quint8>(Command::UpdatePlayerData))) {
        return false;
    }

    if (!FactoryNetObjects::regType<GameData>(
                static_cast<quint8>(Command::GameData))) {
        return false;
    }

    if (!FactoryNetObjects::regType<GetItem>(
                static_cast<quint8>(Command::GetItem))) {
        return false;
    }

    if (!FactoryNetObjects::regType<Player>(
                static_cast<quint8>(Command::Player))) {
        return false;
    }
    return true;
}

}
