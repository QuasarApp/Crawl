#ifndef IWORLDITEM_H
#define IWORLDITEM_H

#include <guiobject.h>

class IWorld;
/**
 * @brief The IWorldItem class This is World item. This class contains functions for control event system.
 */
class IWorldItem: public GuiObject {
    Q_OBJECT
public:
    IWorldItem();

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

private:
    void initOnWorld(const IWorld* world);

    const IWorld* _world = nullptr;
    friend class IWorld;
};

#endif // IWORLDITEM_H
