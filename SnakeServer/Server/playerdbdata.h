#ifndef PLAYERDBDATA_H
#define PLAYERDBDATA_H

#include <player.h>

class PlayerDBData: public ClientProtocol::Player
{
private:
    int lastOnline = 0;
    int onlineTime = 0;

public:
    PlayerDBData();
    int getLastOnline() const;
    void setLastOnline(int value);
    int getOnlineTime() const;
    void setOnlineTime(int value);
};

#endif // PLAYERDBDATA_H
