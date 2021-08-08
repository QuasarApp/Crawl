//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IITEM_H
#define IITEM_H

#include <QString>
#include "global.h"

namespace CRAWL {

/**
 * @brief The IItem class contains base description of the game items (player perks, game levels, and levels items.)
 */
class CRAWL_EXPORT IItem
{
public:
    IItem();

    /**
     * @brief itemTextId All items contains own ids, override this method for create base for generate new item id.
     * @return item text id.
     * @see IItem::itemId
     * @note do not use the tr function for implementation of this method.
     *  If you want to translate the name of the item then use the IItem::itemName method.
     */
    virtual QString itemTextId() const = 0;

    /**
     * @brief itemName This method should be return name of the item.
     * @return Name of the item (translated to all supported languages)
     */
    virtual QString itemName() const = 0;

    /**
     * @brief description This method must be return full description of this item. The description should be translated to all supported languages.
     * @return Full description of this item.
     */
    virtual QString description() const = 0;

    /**
     * @brief image This method should be return path to image preview of the item object.
     * @return path to image form qt resources.
     */
    virtual QString image() const = 0;

    /**
     * @brief cost This method should be return costo to unlock.
     * @return costo to unlock.
     */
    virtual int cost() const = 0;

    /**
     * @brief requiredTier This method return requried level to unlock.
     * @return requried level to unlock.
     */
    virtual int requiredTier() const = 0;

    /**
     * @brief itemId This method return hash of the IItem::itemTextId.
     * @return hash of the IItem::itemTextId.
     * @note The not const implementation inlike const implementation write a id to cache.
     */
    unsigned int itemId();

    /**
     * @brief itemId This method return hash of the IItem::itemTextId.
     * @return hash of the IItem::itemTextId.
     * @warning if the object are const and not const implementation of the IItem::itemId method never invoked then this method return 0.
     */
    unsigned int itemId() const;

private:
    unsigned int _id = 0;
};

}
#endif // IITEM_H
