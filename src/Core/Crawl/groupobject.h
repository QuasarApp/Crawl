//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef GROUPOBJECT_H
#define GROUPOBJECT_H



#include <Crawl/irender.h>
#include <Extensions/claster.h>

namespace CRAWL {

/**
 * @brief The LocalPropertyes struct This structure contains local propertyes of the all childs object of a GroupObject class object.
 */
struct LocalPropertyes {
    QVector3D _position = {0,0,0};
    QQuaternion _rotation = {};
};

/**
 * @brief The GroupObject class is extansion with group object behavior.
 * ### Requeried functions: IWorldItem
 *
 * This class have implementation of the render method that move all child object on selected local positions in parent object.
 *
 * ## Example of use
 *
 * ### For what this object uses
 * This object will be very convinent wher you want to create a difecly claster object with multiple subobjects that should contains in the parrent root object.
 * For example : weapon of the player.
 *
 * ### Example of use
 *
 * 1. create the Player class:
 *
 * ```cpp
 * const QVector3d weaponPosition = {1,0,0};
 * const QQuaternion weaponRotation = QQuaternion::fromEilorAngle(90,0,0);
 *
 * class Player: public IWorldItem, public GroupObject {
 *  //... some implementation
 *  void setWeapon(WeaponObject * weapon) {
 *      installObject(weapon, weaponPosition, weaponRotation);
 *  }
 *  //... some implementation
 * };
 * ```
 *
 * All done. Now the weapon will be static on forward of the Player object.
 *
 * You can change the position and rotation of the weapon object using updatePosition and updateRotation methods.
 */
class GroupObject: public IRender, public Claster
{
public:
    GroupObject();

    void render(unsigned int tbfMsec);

    /**
     * @brief installObject This method is wrapper of the Claster::add method
     * but sets local position and local rotation for an @a object releative current object.
     * @param object This is pointer to the adding object.
     * @param localPosition This is local position of the @a object. The default value is current object center.
     * @param localRotation This is local rotation of the @a object. The default value is invalid quaternion and will be ignored..
     * @note The @a object should be disable own render method of a render method
     * or @a object should not be change position and rotation propertyes
     * @note if you want to ignore the local rotation functionality then set the @a localRotation argument to invalid or default value.
    */
    void installObject(ClasterItem* object,
                       const QVector3D& localPosition = {0,0,0},
                       const QQuaternion& localRotation = {});

    /**
     * @brief updatePosition This method sets new releative position of the child object.
     * @param id This is id of the object that position need to change.
     * @param position This is new value of the object position
      */
    void updatePosition(int id, const QVector3D& position);

    /**
     * @brief updateRotation This method sets new raleative rotation of the object with @a id.
     * @param id This is id of the object that rotation need to change
     * @param roatation This is new value of the object with @a id.
     */
    void updateRotation(int id, const QQuaternion& roatation);

protected:
    /**
     * @brief getLocalrotation This method return current local rotation of the object with @a id.
     * @param id This is id of the object that rotation will be returned.
     * @return current local rotation ot the object winth @a id. IF the object with id not exists on this classter then return nullptr.
     * @warning use this return not const pointer and you can change them value without invoke the updatePosition method but this is not thread safe.
     */
    QQuaternion* getLocalrotation(int id);

    /**
     * @brief getLocalPosition This method return current local position  of the object with @a id.
     * @param id This is id of the object that position will be returned.
     * @return current local position ot the object winth @a id. IF the object with id not exists on this classter then return nullptr.
     * @warning use this return not const pointer and you can change them value without invoke the updateRotation method but this is not thread safe.

     */
    QVector3D* getLocalPosition(int id);

    /**
     * @brief getLocalPropertyes This method return all local propertyes of an object with @a id
     * @param id This is id of the object for getting changes.
     * @return pointer to structure with local propertyes of the object. IF the object with id not exists on this classter then return nullptr.
     * @warning use this return not const pointer and you can change them value but this is not thread safe.
     */
    LocalPropertyes* getLocalPropertyes(int id);


private:
    QHash<int, LocalPropertyes> _extraPropertyes;

};
}
#endif // GROUPOBJECT_H
