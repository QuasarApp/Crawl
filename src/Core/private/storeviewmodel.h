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
    /**
     * @brief visible If you sets thsis proprtye to false then store view qml view will be hide.
    */
    Q_PROPERTY(bool visible READ visible  NOTIFY visibleChanged)

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
    void init(Store * store, User* user);

    /**
     * @brief setUser This method update user pointer
     * @param user This is new pointer to current user.
     */
    void setUser(User* user);

    /**
     * @brief visible This method return true if the store view is visible.
     * @return true if the store view is visible.
     */
    bool visible() const;

    /**
     * @brief setVisible This method chnge the visible state of the qml view of store.
     * @param newVisible This is new value of the qml-store visible
     */
    void setVisible(bool newVisible);

    /**
     * @brief buy This is qml method for receive signal from view about buying item.
     * @param item This is item id that user want to buy.
     */
    Q_INVOKABLE void buy(int item);

signals:
    void visibleChanged();

private:

    enum StoreRoles {
        ItemId,
        ItemName,
        ItemImage,
        ItemDescription,
        ItemWasBuy
    };

    Store *_store = nullptr;
    QList<int> _keys;
    User* _currentUser = nullptr;
    bool _visible = false;
};

}
#endif // STOREVIEWMODEL_H
