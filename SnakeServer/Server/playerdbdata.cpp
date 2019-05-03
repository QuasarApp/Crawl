#include "playerdbdata.h"

int PlayerDBData::getLastOnline() const {
    return lastOnline;
}

void PlayerDBData::setLastOnline(int value) {
    lastOnline = value;
}

int PlayerDBData::getOnlineTime() const {
    return onlineTime;
}

void PlayerDBData::setOnlineTime(int value) {
    onlineTime = value;
}

PlayerDBData::PlayerDBData()
{

}
