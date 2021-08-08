//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef STORE_H
#define STORE_H

#include "user.h"

namespace CRAWL {

class IItem;

/**
 * @brief The Store class contains method for control all game items beetwin users.
 */
class Store
{
public:
    Store();

    /**
     * @brief buy This method unlock the item with @a itemId for @a buyer. The
     * @param buyer This is user that will be buy item with @a itemId id.
     * @param itemId This is id of the item that @a buyer will be buy
     * @return true if the deal gas been completed successfully
     */
    bool buy(User& buyer, int itemId);

    /**
     * @brief init This method initialise store of the game.
     * @param availabelItems This is hash of the available item.
     * @return true if the items inited successfuly else false.
     */
    bool init(const QMultiHash<int, const IItem *> &availabelItems);

    /**
     * @brief getItemById This method return item by id.
     * @param id This is id of the required item.
     * @return pointer to item. if The item with @a id not found then return nullptr.
     */
    const IItem* getItemById(int id) const;

private:
    QMultiHash<int, const IItem*> _store;
};
}
#endif // STORE_H
