//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef CLASTER_H
#define CLASTER_H

#include "Crawl/iworlditem.h"

class ClasterItem;

/**
 * @brief The Claster class are object with support multiple objects render.
 * For example snake with 20 points of the snake blocks.
 * @note The claster object is extansion for the IWorldItems objects.
 */
class CRAWL_EXPORT Claster
{
public:
    Claster();

    virtual ~Claster();

    /**
     * @brief add This method added new object to claster.
     * @param object This is model of added object
     * @note if you want you can override this methods for extend functionality of this class.
     */
    virtual void add(ClasterItem* object);

    /**
     * @brief remove This method remove object from claster
     * @param object poiter of removed object
     */
    virtual void remove(ClasterItem* object);

    /**
     * @brief remove some as a Claster::remove(IWorldItem* object) but by id.
     * @param id of the remved object.
     */
     virtual void remove(int id);

    /**
     * @brief objects This method return list of collected objects.
     * @return return const reference to objects list .
     */
    const QHash<int, ClasterItem*> &objects() const;

private:
    QHash<int, ClasterItem*> _objects;

};

#endif // CLASTER_H
