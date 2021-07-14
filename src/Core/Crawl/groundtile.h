//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef GROUNDTILE_H
#define GROUNDTILE_H

#include "clasteritem.h"

namespace CRAWL {

/**
 * @brief The GroundTile class It reimplementation of the ClasterItem. The groundTile do not heve own render function because the GroundClaster class control position of this class.
 *
 * @note use This class with the GroundClaster class.
 */
class CRAWL_EXPORT GroundTile: public ClasterItem
{
    Q_OBJECT
public:
    GroundTile(const QString& name,
               const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
               QObject *ptr = nullptr);

    // IRender interface
public:

    /**
     * @brief render The current render implementation do nothing.
     * @param tbfMsec This is time betwin frames value. (in milleseconds)
     */
    void render(unsigned int tbfMsec) override;
};
}
#endif // GROUNDTILE_H
