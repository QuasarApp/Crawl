//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <QHash>

#ifndef LEVEL_H
#define LEVEL_H

namespace CRAWL {


class IWorld;
class IItem;
class IPreviewScaneWorld;

/**
 * @brief The ILevel class This interface make the world instance object.
 * All levels libraries should be override this interface.
 *
 */
class ILevel
{
public:
    ILevel() = default;
    virtual ~ILevel();

    /**
     * @brief world This method should be return pointer to the level world.
     * @return pointer to the level world.
     * @see ILevel::setWorld
     */
    IWorld* world() const;

    /**
     * @brief previewScane this method should be create a model of the snake preview scane.
     * @return pointer to the model of the preview scane.
     * @see ILevel::setPreviewScane
     */
    IPreviewScaneWorld* previewScane() const;

    /**
     * @brief reset This method unload all loaded data from level.
     */
    void reset();

    /**
     * @brief availableItems This method return list of the all items of this module.
     * @return list of all items of this level. exept world. for get world object use the ILevel::world method.
     */
    const QMultiHash<int, IItem*>& availableItems() const;

protected:
    /**
     * @brief setWorld This method sets new world pointer.
     * @param newWorld This is new world model object.
     * @note The @a newWorld item will be distroued with the parent object.
     * @see ILevel::world
     */
    void setWorld(IWorld *newWorld);

    /**
     * @brief setPreviewScane This method sets new object for the preview scane.
     * @param newPreviewScane This is new value of the preview scane.
     * @note The @a newPreviewScane item will be distroued with the parent object.
     * @see ILevel::previewScane
     */
    void setPreviewScane(IPreviewScaneWorld *newPreviewScane);

    /**
     * @brief addItem This method add item to the level. Use this method i constructor of the ILevel child class.
     * @param item This is pointer to item
     * @note All added objects will be deleted wint this object.
     */
    void addItem(IItem* item);

private:

    IWorld* _world = nullptr;
    IPreviewScaneWorld* _previewScane = nullptr;
    QMultiHash<int, IItem*> _items;
};

}

#endif // LEVEL_H
