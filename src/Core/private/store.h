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
class ILevel;

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
     * @brief addLevel This method add level objects to store.
     * @return true if the items inited successfuly else false.
     */
    virtual void addLevel(const ILevel* level) = 0;

    /**
     * @brief getItemById This method return item by id.
     * @param id This is id of the required item.
     * @return pointer to item. if The item with @a id not found then return nullptr.
     * @see Store::getItemsByType
     * @see Store::keysListByType
     * @see Store::keysList
     */
    IItem* getItemById(int id) const;

    /**
     * @brief size This method return count of the available items in store.
     * @return count of the available items.
     * @see Store::keysList
     */
    int size() const;

    /**
     * @brief keysList This method return a list of available keys
     * @return a list of available keys
     * @see Store::getItemsByType
     * @see Store::getItemById
     * @see Store::keysListByType
     */
    QList<int> keysList() const;

    /**
     * @brief keysListByType This method return list with ids of all available items for a @a user by @a type.
     * @param type This is type of the requried items
     * @param user This is pointer of the user for that searched items. Skip this param for getting all items by type.
     * @return list with ids of all available items for a @a user by @a type.
     * @see Store::getItemsByType
     * @see Store::getItemById
     * @see Store::keysList

     */
    QList<int> keysListByType(unsigned int type, const User* user = nullptr) const;

    /**
     * @brief getItemsByType This method return list of all available items for a @a user by @a type.
     * @param type This is type of the requried items
     * @param user This is pointer of the user for that searched items. Skip this param for getting all items by type.
     * @return list with ids of all available items for a @a user by @a type.
     * @see Store::keysListByType
     * @see Store::getItemById
     * @see Store::keysList
     */
    QHash<int, IItem*> getItemsByType(unsigned int type, const User* user = nullptr) const;

protected:
    /**
     * @brief addItem This method add item to store.
     * @param item This is item that will be added into store object.
     */
    void addItem(IItem * item);

private:
    QMultiHash<int, QMultiHash<int, IItem *>> _store;
    QMultiHash<int, IItem *> _all;
};
}
#endif // STORE_H
