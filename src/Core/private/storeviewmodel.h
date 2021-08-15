//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef STOREVIEWMODEL_H
#define STOREVIEWMODEL_H

#include "baseuserlistmodel.h"

namespace CRAWL {

class Store;
class User;

/**
 * @brief The StoreViewModel class This is view model of the store. The object of this class should be initialized it he Store class.
 */
class StoreViewModel: public BaseUserListModel
{
    Q_OBJECT
    /**
     * @brief visible If you sets thsis proprtye to false then store view qml view will be hide.
    */
    Q_PROPERTY(bool visible READ visible  NOTIFY visibleChanged)

public:
    StoreViewModel();

    /**
     * @brief init This method initialize data of the view model.
     * @param _store This is poiter to store that contains all inforamtion about store items.
     * @param user This is new pointer to current user.
     * @see StoreViewModel::setUser
     */
    void init(Store * store, User* user);

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

    // BaseUserListModel interface
protected:
    const IItem *getItem(int id) const;

signals:
    /**
     * @brief visibleChanged This slot emited when store visibel changed
     */
    void visibleChanged();

private:

    Store *_store = nullptr;
    bool _visible = false;
};

}
#endif // STOREVIEWMODEL_H
