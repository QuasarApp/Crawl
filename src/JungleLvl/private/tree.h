//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef TREE_H
#define TREE_H

#include <Crawl/iworlditem.h>
#include <jungle_global.h>

namespace JungleLvl {

/**
 * @brief The Tree class
 */
class CRAWL_JUNGLE_LEVEL_EXPORT Tree : public CRAWL::IWorldItem
{
    Q_OBJECT
public:
    Tree();
};
}
#endif // TREE_H
