//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef INVENTORYMODEL_H
#define INVENTORYMODEL_H

#include "baseuserlistmodel.h"

namespace CRAWL {

/**
 * @brief The InventoryModel class This is main model for all inventary views of the game.
 */
class InventoryModel: public BaseUserListModel
{
    Q_OBJECT
public:
    InventoryModel();
};
}
#endif // INVENTORYMODEL_H
