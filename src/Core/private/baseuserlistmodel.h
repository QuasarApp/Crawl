//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef BASEUSERLISTMODEL_H
#define BASEUSERLISTMODEL_H

#include <QAbstractListModel>

namespace CRAWL {

class User;
class IItem;

/**
 * @brief The BaseUserListModel class This is base class wint implementation methods for working with user object.
 */
class BaseUserListModel: public QAbstractListModel
{
    Q_OBJECT
public:
    BaseUserListModel();

    /**
     * @brief setUser This method update user pointer
     * @param user This is new pointer to current user.
     */
    void setUser(User *newUser);

    /**
     * @brief keys This method retutn curent visible items list.
     * @return visible items list.
     * @see BaseUserListModel::setKeys
     */
    const QList<int> &keys() const;

    /**
     * @brief setKeys This method sets lsit of the keys for view.
     * @param visibleKeysList This is new valud of the visible keys list.
     * @see BaseUserListModel::keys
     */
    void setKeys(const QList<int>& visibleKeysList);

    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

protected:

    /**
     * @brief getUser This method return pointer to current user.
     * @return pointer to current user.
     */
    User* getUser() const;

    /**
     * @brief handleUnlockedItem This slot invoked when emited the User::unclokItem signal.
     * @param item This is id of the unlocked item
     */
    virtual void handleUnlockedItem(int item);

    /**
     * @brief handleUnlockedItem This slot invoked when emited the User::droppItem signal.
     * @param item This is id of the dropped item
     */
    virtual void handleDroppedItem(int item);

    /**
     * @brief handleUnlockedItem This slot invoked when emited the User::setUnlockedItems signal.
     * @param item This is new list of the unclod items.
     */
    virtual void handleUnlockedItemsListChanged(const QSet<int>& newSet);

    /**
     * @brief getItem This method should be return the item by id. Override this method for correct works this model.
     * @param id This is item id
     * @return const pointer to item object.
     */
    virtual const IItem* getItem(int id) const = 0;

    /**
     * @brief getIndexById This method return index of the item by id.
     * @param id This is id of the needed item
     * @return index of the needed item. If the item with id not exists then return -1
     */
    int getIndexById(int id) const;
private:

    enum ViewItemRoles {
        ItemId,
        ItemName,
        ItemImage,
        ItemDescription,
        ItemWasBuy
    };

    User * _user = nullptr;
    QList<int> _keys;
    QHash<int, int> _keysIndexes;
};

}
#endif // BASEUSERLISTMODEL_H
