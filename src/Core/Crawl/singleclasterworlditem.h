//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef SINGLECLASTERWORLDITEM_H
#define SINGLECLASTERWORLDITEM_H

#include "clasteritem.h"

namespace CRAWL {

class Claster;

/**
 * @brief The SingleClasterWorldItem class This is wraper of the OWorldOitem for the controll parent clasters.
 * This object can belong to only one cluster in one time
 */
class CRAWL_EXPORT SingleClasterWorldItem: public ClasterItem
{
    Q_OBJECT
public:
    SingleClasterWorldItem(const QString& name,
                           const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
                           QObject *ptr = nullptr);
protected:

    /**
     * @brief setClaster invoked when object added to new claster.
     * @param claster pointer to invoker claster object.
     * @note This implementation can be sets only one object as a parent.
     */
    void setClaster(Claster *claster) override;

    /**
     * @brief parentClaster This method is wraper of the ClasterItem::parentClasters method.
     * @return pointer  to the parent claster object.
     */
    Claster* parentClaster() const;

    friend class Claster;
};
}

#endif // SINGLECLASTERWORLDITEM_H
