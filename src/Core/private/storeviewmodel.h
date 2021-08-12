//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef STOREVIEWMODEL_H
#define STOREVIEWMODEL_H

#include <QAbstractListModel>

namespace CRAWL {

class Store;
class User;

/**
 * @brief The StoreViewModel class This is view model of the store. The object of this class should be initialized it he Store class.
 */
class StoreViewModel: public QAbstractListModel
{
    Q_OBJECT
public:
    StoreViewModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = {}) const override;
    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief init This method initialize data of the view model.
     * @param _store This is poiter to store that contains all inforamtion about store items.
     * @param user This is new pointer to current user.
     * @see StoreViewModel::setUser
     */
    void init(const Store * store, const User* user);

    /**
     * @brief setUser This method update user pointer
     * @param user This is new pointer to current user.
     */
    void setUser(const User* user);
private:

    enum StoreRoles {
        ItemId,
        ItemName,
        ItemImage,
        ItemDescription,
        ItemWasBuy
    };

    const Store *_store = nullptr;
    QList<int> _keys;
    const User* _currentUser = nullptr;
};

}
#endif // STOREVIEWMODEL_H
