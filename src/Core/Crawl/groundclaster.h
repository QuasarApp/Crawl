//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef GROUNDCLASTER_H
#define GROUNDCLASTER_H

#include "Extensions/autogenerateclaster.h"
#include "global.h"
#include "Crawl/iworlditem.h"

namespace CRAWL {

/**
 * @brief The GroundClaster class This is main control class for background plates of the world.
 * Default behavior: create the tile grid and move old tiles to end of the world.
 */
class CRAWL_EXPORT GroundClaster: public IWorldItem, public AutoGenerateClaster {

    Q_OBJECT

public:
    GroundClaster(const QString& name,
            const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
            QObject *ptr = nullptr);

    // IRender interface
    void render(unsigned int tbfMsec) override;

    void add(ClasterItem *object) override;
    void remove(ClasterItem *object) override;
    void remove(int id) override;
    void init() override;
    unsigned int itemsCount() const override;

protected:

    /**
     * @brief newObjectDistance This method should be return default distance betwin clstersItems
     * @return default distance betwin clstersItems
     * @note By default this value equals 2000 points
     */
    virtual int newObjectDistance() const;

private:
    QList<IWorldItem*> _itemsOrder;
    unsigned int _index = 0;

};

}

#endif // GROUNDCLASTER_H
