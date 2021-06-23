#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "iworlditem.h"

/**
 * @brief The MovableObject class contains functions for moving object on the world.
 * All moving separate to next properties:
 *
 * * **Movable vector** This property sets direction of move
 * * **Movable vector force** This is force of the movable vector.
 * * **Angular velocity** This property sets spead of the angle moving.
 * * **Braking force** This property are delta decriment the Power of the movable vector on time.
 */
class CRAWL_EXPORT MovableObject: public IWorldItem
{
    Q_OBJECT
public:
    MovableObject(const QString& name,
                  const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
                  QObject *ptr = nullptr);

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
     * @param newMovableVector - this is a new value ofthe movable vector
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

private:
    QVector3D _movableVector;
    QVector3D _currentMovableVector;

    float _angularVelocity = 0;
    float _breakingForce = 0;

};

#endif // MOVABLEOBJECT_H
