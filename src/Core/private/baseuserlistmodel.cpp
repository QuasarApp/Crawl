//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "baseuserlistmodel.h"
#include "user.h"
#include "store.h"
#include <Crawl/iitem.h>

namespace CRAWL {

BaseUserListModel::BaseUserListModel() {

}

void BaseUserListModel::setUser(User *newUser) {
    if (_user) {
        disconnect(_user, &User::sigDropped,
                   this, &BaseUserListModel::handleDroppedItem);
        disconnect(_user, &User::sigUnlcoked,
                   this, &BaseUserListModel::handleUnlockedItem);
        disconnect(_user, &User::sigUlockedItemsChanged,
                   this, &BaseUserListModel::handleUnlockedItemsListChanged);
    }

    _user = newUser;

    if (_user) {
        connect(_user, &User::sigDropped,
                this, &BaseUserListModel::handleDroppedItem);
        connect(_user, &User::sigUnlcoked,
                this, &BaseUserListModel::handleUnlockedItem);
        connect(_user, &User::sigUlockedItemsChanged,
                this, &BaseUserListModel::handleUnlockedItemsListChanged);
    }
}

int BaseUserListModel::getIndexById(int id) const {
    return _keysIndexes.value(id, -1);
}

Store *BaseUserListModel::store() const {
    return _store;
}

void BaseUserListModel::setStore(Store *newStore) {
    _store = newStore;
}

const QList<int> &BaseUserListModel::keys() const {
    return _keys;
}

void BaseUserListModel::setKeys(const QList<int> &visibleKeysList) {
    int diff = visibleKeysList.size() - _keys.size();

    auto update = [this](const QList<int> & list) {
        _keys = list;
        for (int index = 0; index < _keys.size(); ++index) {
            _keysIndexes[_keys[index]] = index;
        }
    };

    if (diff > 0) {
        beginInsertRows({}, _keys.size(), visibleKeysList.size() - 1);
        update(visibleKeysList);
        endInsertRows();

    } else if (diff == 0) {
        emit dataChanged(index(0,0), index(rowCount() - 1, columnCount() - 1));

    } else  {
        beginRemoveRows({}, visibleKeysList.size(), _keys.size() - 1);
        update(visibleKeysList);
        endRemoveRows();
    }
}

void BaseUserListModel::addKey(int newKey) {
    beginInsertRows({}, _keys.size(), _keys.size());
    _keys.push_back(newKey);
    _keysIndexes[newKey] = _keys.size() - 1;
    endInsertRows();
}

void BaseUserListModel::removeKey(int oldKey) {
    int idx = getIndexById(oldKey);

    if (idx >= 0) {
        beginRemoveRows({}, _keys.size(), _keys.size());

        _keys.removeAt(idx);
        _keysIndexes.remove(oldKey);

        endRemoveRows();

    }
}

int BaseUserListModel::rowCount(const QModelIndex &) const {
    return _keys.size();
}

int BaseUserListModel::columnCount(const QModelIndex &) const {
    return 1;
}

QVariant BaseUserListModel::data(const QModelIndex &index, int role) const {

    if (index.row() >= rowCount()) {
        return {};
    }

    int id = _keys.at(index.row());

    const IItem* item = getItem(id);

    if (!item)
        return {};

    switch (role) {
    case ItemId: return id;
    case ItemName: return item->itemName();
    case ItemImage: return item->image();
    case ItemDescription: return item->description();
    case ItemWasBuy: return getUser() && getUser()->isUnlocked(id);
    default:
        return {};
    }
}

QHash<int, QByteArray> BaseUserListModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[ItemId] = "itemId";
    roles[ItemName] = "itemName";
    roles[ItemDescription] = "itemDescription";
    roles[ItemImage] = "itemImage";
    roles[ItemWasBuy] = "itemWasBuy";

    return roles;
}

User *BaseUserListModel::getUser() const {
    return _user;
}

void BaseUserListModel::handleUnlockedItem(int item) {
    int idx = _keysIndexes.value(item, -1);

    if (idx >= 0) {
        emit dataChanged(index(idx,0), index(idx, 0), {ItemWasBuy});
    }
}

void BaseUserListModel::handleDroppedItem(int item) {
    int idx = _keysIndexes.value(item, -1);

    if (idx >= 0) {
        emit dataChanged(index(idx,0), index(idx, 0), {ItemWasBuy});
    }
}

void BaseUserListModel::handleUnlockedItemsListChanged(const QSet<int> &) {
    emit dataChanged(index(0,0), index(_keys.size() - 1, 0), {ItemWasBuy});
}

const IItem *BaseUserListModel::getItem(int id) const {
    return _store->getItemById(id);
}

}
