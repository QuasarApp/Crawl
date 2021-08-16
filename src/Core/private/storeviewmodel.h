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
     * @brief buy This is qml method for receive signal from view about buying item.
     * @param item This is item id that user want to buy.
     */
    Q_INVOKABLE void buy(int item);

    // BaseUserListModel interface
protected:
    const IItem *getItem(int id) const;

};

}
#endif // STOREVIEWMODEL_H
