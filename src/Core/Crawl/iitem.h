//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IITEM_H
#define IITEM_H

#include <QList>
#include <QSet>
#include <QString>
#include "global.h"

/**
 * @brief IITEM_OBJECT This macross init the item id for child IItem classes.
 * For each items with this macross automaticly added two method:
 *  - staticTextId This is static method that return text value of the object.
 *  - staticId This is static method that return integer value of the item object.
*/
#define IITEM_OBJECT(ObjectTextID) \
    public: \
        QString itemTextId() const override { return ObjectTextID } \
        static QString staticTextId() { return ObjectTextID}; \
        static QString staticId() { return qHash(ObjectTextID)};


namespace CRAWL {

/**
 * @brief The ChildIteAction struct contains two lambda function with actions for remove and add item to a parent item.
 * The parent can be run any actions when item added or dropped.
 */
struct ChildItemAction {
    /**
     * @brief _onAdded This actions for added item to parent
     */
    std::function<void()> _onAdded = {nullptr};
    /**
     * @brief _onDropped This action for remove item from parent
     */
    std::function<void()> _onDropped = {nullptr};

    /**
     * @brief isValid This method check this structure to valid. The object is valid when all actions is inited else invalid.
     * @return true if this object is valid else false.
     */
    bool isValid() const;
};

/**
 * @brief The IItem class contains base description of the game items (player perks, game levels, and levels items.)
 * Each item contains own unique text id. The unique text id should be implemented in the staticTextId function. This functions must be static.
 *  Each items must be contains the IITEM_OBJECT macross.
 * @code{cpp}
 * class MyItem : public IItem {
 *  IITEM_OBJECT ("ItemTextId")
 * ...
 * }
 * @endcode
 * @see IITEM_OBJECT
 * @note You can use the IITEM_OBJECT macross and staticTextId. This macros create default implementation of the itemTextId method;
 * If you implements the staticTextId you can use the IITEM_OBJECT macross.
 */
class CRAWL_EXPORT IItem
{
public:
    IItem();
    virtual ~IItem() = default;

    /**
     * @brief itemTextId All items contains own ids, override this method for create base for generate new item id.
     * @return item text id.
     * @see IItem::itemId
     * @note do not use the tr function for implementation of this method.
     *  If you want to translate the name of the item then use the IItem::itemName method.
     */
    virtual QString itemTextId() const = 0;

    /**
     * @brief itemTextType This method return text of the item group or type.
     * @return text of the item group of type.
     * @see IITem::itemType
     */
    virtual QString itemTextType() const = 0;

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
     * @brief childItems This method shold be return list of the child items available for unlocked for this item.
     * @return list of the child items pointers.
     * @note The child items connot be removed automaticalu. All child items will be removed in the Store object.
     * @see IItem::addChildItem
     * @see IItem::childItemsRecursive
     * @see IItem::getChildActions
     */
    const QHash<int, ChildItemAction> &childItems() const;

    /**
     * @brief getChild This method return structure with dropp and add actions for the item.
     * @param id This is id of the child object.
     * @return structure with dropp and add actions for the item.
     * @note if The item with @a id not found then return invalid Actions object. @see ChildItemAction::isValid
     * @see IItem::childItems
     * @see IItem::addChildItem
     * @see IItem::childItemsRecursive
     */
    ChildItemAction getChildActions(int id) const;

    /**
     * @brief registerActions This method add to this item actions for item with an @a itemID
     * @param itemID This id of the item that will be registered.
     * @param action This is actions structure for an @a itemID
     */
    void registerActions(int itemID, const ChildItemAction& action);

    /**
     * @brief itemId This method return hash of the IItem::itemTextId.
     * @return hash of the IItem::itemTextId.
     * @see IItem::itemTextId
     * @note The not const implementation inlike const implementation write a id to cache.
     */
    unsigned int itemId();

    /**
     * @brief itemId This method return hash of the IItem::itemTextId.
     * @return hash of the IItem::itemTextId.
     * @see IItem::itemTextId
     * @warning This method not cached id value, so works sloyle then not cons implementation.
     */
    unsigned int itemId() const;

    /**
     * @brief itemType This method return item type id. (items group)
     * @return item type id.
     * @see IItem::itemTextType
     * @note The not const implementation inlike const implementation write a id to cache.
     */
    unsigned int itemType();

    /**
     * @brief itemType This method return item type id. (items group)
     * @return item type id.
     * @see IItem::itemTextType
     * @warning This method not cached id value, so works sloyle then not cons implementation.
     */
    unsigned int itemType() const;

    /**
     * @brief activeItems This method return set of the actived items.
     * @return set of the actived items.
     * @see IItem::setActiveItems
     * @see IItem::activate
     * @see IItem::deactivate
     * @see IItem::isActive
     */
    const QSet<int> &activeItems() const;

    /**
     * @brief setActiveItems This method sets new set of the actived items.
     * @param newActiveItems This is new set of the ctived items.
     * @see IItem::activeItems
     * @see IItem::activate
     * @see IItem::deactivate
     * @see IItem::isActive
     */
    virtual void setActiveItems(const QSet<int> &newActiveItems);

    /**
     * @brief activate This method activate the child item with @a item id of this item.
     * @param item activated item id.
     * @see IItem::setActiveItems
     * @see IItem::activeItems
     * @see IItem::deactivate
     * @see IItem::isActive
     */
    void activate(int item);

    /**
     * @brief deactivate This method deactivate the child item with @a item id of this item.
     * @param item deactivated item id.
     * @see IItem::setActiveItems
     * @see IItem::activate
     * @see IItem::activeItems
     * @see IItem::isActive
     */
    void deactivate(int item);

    /**
     * @brief isActive This method will be return true if the @a item is actived. else false. If the item not child item of this object the this method return false.
     * @param item This is checked item id.
     * @return true if the @a item is actived. else false. If the item not child item of this object the this method return false.
     * @see IItem::setActiveItems
     * @see IItem::activate
     * @see IItem::deactivate
     * @see IItem::activeItems
     */
    bool isActive(int item);

private:
    unsigned int _id = 0;
    unsigned int _typeItem = 0;
    QHash<int, ChildItemAction> _childs;
    QSet<int> _activeItems;

};

}
#endif // IITEM_H
