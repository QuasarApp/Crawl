//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "Extensions/basemotion.h"
#include <QQuaternion>
#include <QVector3D>

namespace CRAWL {


class GuiObject;

/**
 * @brief The MovableObject class contains functions for moving object on the world.
 * All moving separate to next properties:
 *
 * * **Movable vector** This property sets direction of move
 * * **Movable vector force** This is force of the movable vector.
 * * **Angular velocity** This property sets spead of the angle moving.
 * * **Braking force** This property are delta decriment the Power of the movable vector on time.
 */
class CRAWL_EXPORT MovableObject: public BaseMotion
{

public:
    MovableObject();

    /**
     * @brief render This impplementation of the render method add simulation of the physics in the vacuum space.
     * @param tbfMsec This is time betwin frames argument.
     */
    void render(unsigned int tbfMsec) override;

    /**
     * @brief movableVector This method return current mvable vector.
     * The movable vector it is second point of line betwin object center and movableVector point.
     * The movableVector base on own releative asix system wher the object center is vector {0 0 0}
     * @note So movableVector are 3d angle of the moving of this object.
     * @return movable vector of object
     */
    const QVector3D &movableVector() const;

    /**
     * @brief setMovableVector This method sets new value of the mvable vector.
     * @param newMovableVector this is a new value ofthe movable vector
     * @note The movable vector will be changed in time if you set the MovableObject::breakingForce property to non 0 value.
     */
    void setMovableVector(const QVector3D &newMovableVector);

    /**
     * @brief angularVelocity This method return current angular veloscity.
     * @return angular velosity
     * @note This property contains speed on angle per second (a/s)
     */
    float angularVelocity() const;

    /**
     * @brief setAngularVelocity This method sets new value of the angular velacity in angele per second
     * @param newAngularVelocity This is new value of the angular velacity
     */
    void setAngularVelocity(float newAngularVelocity);

    /**
     * @brief breakingForce This method return current value of the breaking force.
     * @return urrent value of the breaking force
     */
    float breakingForce() const;

    /**
     * @brief setBreakingForce This method sets new value of the breaking force.
     * @param newBreakingForce This is new value of the breaking force
     */
    void setBreakingForce(float newBreakingForce);

    /**
     * @brief currentMovableVector This method return current movable vector.
     * @return current movable vector.
     */
    const QVector3D &currentMovableVector() const;

protected:

    /**
     * @brief renderRotation This method recalc raration for an @a object. The Default implementation converts movableVector to rotation of an @a object.
     * @param object This is provessing object. Usually @a an object is casted pointer of this to GuiObject type.
     * @param tbfMsec This is time betwin frames argument. soame as in the IRender::render function.
     */
    void renderRotation(GuiObject* object, unsigned int tbfMsec) override;

    /**
     * @brief renderRotation This method recalc position for an @a object. The Default implementation move the current movable vector to setts movable vector. For example if you invoke the MovableObject::setMovableVector method then object change current movable vector with spead MovableObject::angularVelocity. If you sets
     * @param object This is provessing object. Usually @a an object is casted pointer of this to GuiObject type.
     * @param tbfMsec This is time betwin frames argument. soame as in the IRender::render function.
     */
    void renderPosition(GuiObject* object, unsigned int tbfMsec) override;

private:
    QVector3D _movableVector;
    QVector3D _currentMovableVector;
    QQuaternion _staticRotation = QQuaternion::fromEulerAngles(0,0,0);

    float _angularVelocity = 0;
    float _breakingForce = 0;
};

}

#endif // MOVABLEOBJECT_H
