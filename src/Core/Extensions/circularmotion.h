//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <Crawl/irender.h>

#include <QVector3D>

#ifndef CIRCULARMOTION_H
#define CIRCULARMOTION_H

namespace CRAWL {

/**
 * @brief The CircularMotion class. This class contains render function for the moving guiobject by round.
 * @note For motion set motion asix and angular velocity
 */
class CRAWL_EXPORT CircularMotion: public IRender
{
public:
    CircularMotion(const QVector3D* center);

    // IRender interface
public:
    void render(unsigned int tbfMsec) override;

    /**
     * @brief angularVelocity This is property are speed of motion.
     * @return current speed of the motion object.
     */
    float angularVelocity() const;

    /**
     * @brief setAngularVelocity This method sets new value of the current speed of the object.
     * @param newAngularVelocity This is new value of the motion speed
     */
    void setAngularVelocity(float newAngularVelocity);

    /**
     * @brief axis This method are asix of motion. This object will moving around this axis.
     * @return curretn asix value.
     */
    const QVector3D &axis() const;

    /**
     * @brief setAxis This method sets new value of the motion axis.
     * @param newAxis This is new value of the motion asix.
     */
    void setAxis(const QVector3D &newAxis);

    /**
     * @brief radius This method return current radius of the circular motion
     * @return current radius
     */
    float radius() const;

    /**
     * @brief setRadius This method sets new value of the circular motion radius.
     * @param newRadius This is new value of the circular motion radius.
     */
    void setRadius(float newRadius);

    /**
     * @brief anglePosition This method return current angel of the item position arountd center.
     * @return current angle position around center.
     */
    double anglePosition() const;

    /**
     * @brief setAnglePosition This method sets new angel of the item position arountd center.
     * @return newAngle angle position around center.
     */
    void setAnglePosition(double newAngle);

private:
    float _angularVelocity = 0;
    QVector3D _axis;
    const QVector3D *_center = nullptr;
    float _radius;
    double _angle = 0;

};

}
#endif // CIRCULARMOTION_H
