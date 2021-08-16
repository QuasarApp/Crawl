//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef GROUNDPLATE_H
#define GROUNDPLATE_H

#include "Crawl/groundtile.h"

namespace JungleLvl {

/**
 * @brief The GroundPlate class
 */
class GroundPlate: public CRAWL::GroundTile
{
    Q_OBJECT
    Q_PROPERTY(int tiliesCount READ tiliesCount WRITE setTiliesCount NOTIFY tiliesCountChanged)

public:
    GroundPlate();

    int tiliesCount() const;
    void setTiliesCount(int newTiliesCount);

signals:
    void tiliesCountChanged();

private:
    int _tiliesCount = 1;
};
}
#endif // GROUNDPLATE_H
