//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef PLAYER_H
#define PLAYER_H

#include "icontrol.h"

namespace CRAWL {

/**
 * @brief The Player class is main class of users.
 */
class CRAWL_EXPORT Player: public IControl
{
    Q_OBJECT
public:
    Player();
};
}
#endif // PLAYER_H
