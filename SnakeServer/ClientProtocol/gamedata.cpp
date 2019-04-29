#include "gamedata.h"
#include "config.h"


namespace ClientProtocol {

GameData::GameData()
{

}

QList<int> GameData::getTimeClick() const {
    return timeClick;
}

void GameData::setTimeClick(const QList<int> &value) {
    timeClick = value;
}

int& GameData::operator[](int index) {
    return timeClick[index];
}

BaseNetworkObject *GameData::create() const {
    return new GameData();
}

NetworkClassSize GameData::classSize() const {
    return UpdatePlayerData::classSize() +
            getTypeSize(timeClick);
}

QDataStream &GameData::writeToStream(QDataStream &stream) const {
    UpdatePlayerData::writeToStream(stream);
    stream << timeClick;
    return stream;
}

QDataStream &GameData::readFromStream(QDataStream &stream) {
    UpdatePlayerData::readFromStream(stream);
    stream >> timeClick;
    return stream;
}

bool GameData::isValid() const {
    return timeClick.size() > 0 && UpdatePlayerData::isValid();
}

}
