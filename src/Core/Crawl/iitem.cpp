//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "iitem.h"
#include <QHash>

namespace CRAWL {

IItem::IItem() {

}

unsigned int IItem::itemId() {
    if (_id) {
        return _id;
    }

    _id = qHash(itemTextId());
    return _id;
}

unsigned int IItem::itemId() const {
    return _id;
}
}
