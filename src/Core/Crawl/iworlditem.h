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

namespace CRAWL {

class IWorld;
/**
 * @brief The IWorldItem class This is World item. This class contains functions for control event system.
 */
class CRAWL_EXPORT IWorldItem: public GuiObject {
    Q_OBJECT

public:
    IWorldItem(const QString& name,
               const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
               QObject *ptr = nullptr);

    const IWorld *world() const;

    /**
     * @brief render This implementation move objects from end of scane to begin.
     * @param tbfMsec
     * @note new position = playerPosition + scaneSize;
     */
    void render(unsigned int tbfMsec) override;
    void init() override;

    /**
     * @brief isDecorative This method return true if the object is decarative.
     *  The decorative objects not patricipate in event process.
     * @return true if this ovjects is decorative.
     */
    bool isDecorative() const;

    /**
     * @brief supportedEvents This method return mask of the supported events. For get more information about events see the CRAWL::Events enum.
     * @return integer mask of the supported events.
     * @see IWorldItem::setSupportedEvents
     * @see IWorldItem::addSupportOfEvent
     * @see IWorldItem::dropSupportOfEvent
     * @see IWorldItem::supportedEvents
     */
    int supportedEvents() const;

    /**
     * @brief isSopportEvent This method return true ithis objects support a @a event.f
     * @return true if this objects support a @a event else false.
     * @note If a @a event is mask with multiple events the this method return true if this objects support all events from a @a event mask.
     */
    bool isSopportEvent(int event) const;

    /**
     * @brief destroy this method will schedule a destroing of this object on the world.
     * @see IWorldItem::destroyIsScheduled
     */
    virtual void destroy();

    /**
     * @brief respawn this method will schedule a repawning of this object on the world.
     */
    virtual void respawn();

    /**
     * @brief destroyIsScheduled This method return true if the current object has been scheduled to destroy.
     * @return true if the current object has been scheduled to destroy, else false.
     * @see IWorldItem::destroy
     */
    bool destroyIsScheduled() const;

    /**
     * @brief action This method contains actions releative another game objects.
     * @param item This is pointer to item that will be interaction with this object.
     * @note The default implementation do nothing.
     */
    virtual void action(IWorldItem* item);

protected:

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

    /**
     * @brief setFDecorative This method sets if object declarative or physical.
     * @param newFDecorative new value of the fDecorative property
     */
    void setFDecorative(bool newFDecorative);

    /**
     * @brief setSupportedEvents This method overwrite the mask og the supported events.
     * @param newSupportedEvents This is new value of the supported events mask.
     * @see IWorldItem::setSupportedEvents
     * @see IWorldItem::addSupportOfEvent
     * @see IWorldItem::dropSupportOfEvent
     * @see IWorldItem::supportedEvents
     */
    void setSupportedEvents(int newSupportedEvents);

    /**
     * @brief addSupportOfEvent This method add support of a @a newSupportedEvent.
     * @param newSupportedEvent This is new value of a supported event.
     * @see IWorldItem::setSupportedEvents
     * @see IWorldItem::addSupportOfEvent
     * @see IWorldItem::dropSupportOfEvent
     * @see IWorldItem::supportedEvents
     */
    void addSupportOfEvent(int newSupportedEvent);

    /**
     * @brief dropSupportOfEvent This method drop support of a @a depricatedEvent
     * @param depricatedEvent This is event that will be dropped.
     * @see IWorldItem::setSupportedEvents
     * @see IWorldItem::addSupportOfEvent
     * @see IWorldItem::dropSupportOfEvent
     * @see IWorldItem::supportedEvents
     */
    void dropSupportOfEvent(int depricatedEvent);

private:
    void initOnWorld(const IWorld* world);

    const IWorld* _world = nullptr;

    bool _fDecorative = true;
    bool _fDistroy = false;
    int _supportedEvents;

    friend class IWorld;
};
}
#endif // IWORLDITEM_H
