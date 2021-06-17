//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IWORLDITEM_H
#define IWORLDITEM_H

#include <Crawl/guiobject.h>
#include "global.h"

class IWorld;
/**
 * @brief The IWorldItem class This is World item. This class contains functions for control event system.
 */
class CRAWL_EXPORT IWorldItem: public GuiObject {
    Q_OBJECT
public:
    IWorldItem();

    const IWorld *world() const;

    /**
     * @brief render This implementation move objects from end of scane to begin.
     * @param tbfMsec
     * @note new position = playerPosition + scaneSize;
     */
    void render(unsigned int tbfMsec) override;

protected:

    /**
     * @brief onIntersects This is intersect event betwin this and subscribet objects.
     * @param item This is pointer to the event object.
     */
    virtual void onIntersects(const IWorldItem *item) = 0;

    /**
     * @brief getItem This method return item world by id. If object is not exits then return nullptr.
     * @return constant pointer tot the item world.
     */
    const IWorldItem * getItem(int id) const;

    /**
     * @brief getPlayer This method return pointer to player object.
     * @return raw pointer to playerObject
     */
    const IWorldItem * getPlayer() const;



private:
    void initOnWorld(const IWorld* world, const IWorldItem *player);

    const IWorld* _world = nullptr;
    const IWorldItem *_playerObject = nullptr;
    friend class IWorld;

};

#endif // IWORLDITEM_H
