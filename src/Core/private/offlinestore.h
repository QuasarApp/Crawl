//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef OFFLINESTORE_H
#define OFFLINESTORE_H

#include "store.h"

namespace CRAWL {

/**
 * @brief The OfflineStore class This is offiline implementation of the store object.
 */
class OfflineStore : public Store
{
public:
    OfflineStore();

    void addLevel(const ILevel *level) override;
};

}
#endif // OFFLINESTORE_H
