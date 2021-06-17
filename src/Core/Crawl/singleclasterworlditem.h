//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef SINGLECLASTERWORLDITEM_H
#define SINGLECLASTERWORLDITEM_H

#include "iworlditem.h"

class Claster;

/**
 * @brief The SingleClasterWorldItem class This is wraper of the OWorldOitem for the controll parent clasters.
 * This object can belong to only one cluster in one time
 */
class CRAWL_EXPORT SingleClasterWorldItem: public IWorldItem
{
public:
    SingleClasterWorldItem();

private:

    /**
     * @brief setClaster invoked when object added to new claster.
     * @param claster pointer to invoker claster object.
     */
    void setClaster(Claster *claster);

    Claster* _parentClaster = nullptr;

    friend class Claster;
};

#endif // SINGLECLASTERWORLDITEM_H
