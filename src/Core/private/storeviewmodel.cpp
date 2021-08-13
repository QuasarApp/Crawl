#include "storeviewmodel.h"
#include "store.h"
#include "user.h"

#include <Crawl/iitem.h>

namespace CRAWL {

StoreViewModel::StoreViewModel() {

}

QModelIndex StoreViewModel::index(int row, int column, const QModelIndex &parent) const {
    return QAbstractListModel::index(row, column, parent);
}

int StoreViewModel::rowCount(const QModelIndex &) const {
    return _keys.size();
}

int StoreViewModel::columnCount(const QModelIndex &) const {
    return 1;
}

QVariant StoreViewModel::data(const QModelIndex &index, int role) const {
    if (!_store)
        return {};

    if (index.row() >= rowCount()) {
        return {};
    }

    int id = _keys.at(index.row());

    const IItem* item = _store->getItemById(id);

    if (!item)
        return {};

    switch (role) {
    case ItemId: return id;
    case ItemName: return item->itemName();
    case ItemImage: return item->image();
    case ItemDescription: return item->description();
    case ItemWasBuy: return _currentUser && _currentUser->isUnlocked(id);
    default:
        return {};
    }
}

QHash<int, QByteArray> StoreViewModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[ItemId] = "itemId";
    roles[ItemName] = "itemName";
    roles[ItemDescription] = "itemDescription";
    roles[ItemImage] = "itemImage";
    roles[ItemWasBuy] = "itemWasBuy";

    return roles;
}

void StoreViewModel::init(Store *store, User *user) {
    setUser(user);

    int diff = store->size() - _keys.size();

    if (diff > 0) {
        beginInsertRows({}, _keys.size(), store->size() - 1);

        _store = store;
        _keys = store->keysList();

        endInsertRows();

    } else if (diff == 0) {
        emit dataChanged(index(0,0), index(rowCount() - 1, columnCount() - 1));

    } else  {
        beginRemoveRows({}, store->size(), _keys.size() - 1);

        _store = store;
        _keys = store->keysList();

        endRemoveRows();
    }
}

void StoreViewModel::setUser(User *user) {
    _currentUser = user;
    emit dataChanged(index(0,0), index(rowCount() - 1, columnCount() - 1), {ItemWasBuy});
}

bool StoreViewModel::visible() const {
    return _visible;
}

void StoreViewModel::setVisible(bool newVisible) {
    if (_visible == newVisible)
        return;
    _visible = newVisible;
    emit visibleChanged();
}

void StoreViewModel::buy(int item) {
    if (_store && _currentUser) {
        _store->buy(*_currentUser, item);
    }
}
}
