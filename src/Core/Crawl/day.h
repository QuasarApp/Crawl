//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef DAY_H
#define DAY_H

#include "Extensions/claster.h"
#include "dayitem.h"
#include "iworlditem.h"
#include "math.h"

namespace CRAWL {

template <class Sun, class Moon>

/**
 * @brief The Day class is template wrapper for the moon and sun objects.
 * The moon and sun objects moving around world center for imitation of the day.
 *
 * ### Integration on the world.
 * You need to add one object of this class in the IWorld::initWorldRules method.
 * **Example:**
 *
 * ```cpp
 * CRAWL::WorldRule *World::initWorldRules() {

    using Day = CRAWL::Day<CRAWL::Sun, CRAWL::Moon>;

    return new CRAWL::WorldRule {
        {0, {
                {registerObject<Day>(), 1},
            }
        },
        {1000, {
                {registerObject<Day>(), 1},
            }
        },
    };
}
 * ```
 * @note All objects will be moving around this objects with radius. The Radius by default is 1000.
 * @note This class automaticly sets ligth force for the light objects.
 *
 *
 */
class Day: public IWorldItem, public Claster
{

public:
    Day(): IWorldItem(AUTO_CLASS_NAME) {

        static_assert(std::is_base_of_v<DayItem, Sun>,
                "The Day class can be works only with DayItem child classes");

        DayItem* sun = new Sun(&position());
        DayItem* moon = new Moon(&position());

        sun->setAnglePosition(0);
        moon->setAnglePosition(180);

        add(sun);
        add(moon);

    }

    void render(unsigned int ) override {
        setposition(getPlayer()->position() + QVector3D{0, 0, 0});
    }

    void add(ClasterItem *object) override {

        if (auto item = dynamic_cast<DayItem*>(object)) {
            item->setRadius(radius());
            item->setAxis(_axis);
            item->setAngularVelocity(lengthToSpeed(_dayLengthSec));
            item->setLightForce(lengthForce());

            Claster::add(item);
        } else {
            QuasarAppUtils::Params::log("The Day class can works only with "
                                        " Child classes of the DayItem",
                                        QuasarAppUtils::Error);

        }
    };

    void remove(ClasterItem *object) override {
        Claster::remove(object);
    };

    /**
     * @brief radius This method return radius of the motion day objects.
     * @return radius of the motions
     */
    int radius() const {
        return _radius;
    }

    /**
     * @brief setRadius This method sets new value of the motions radius.
     * @param newRadius This is new value o fthe motion.
     */
    void setRadius(int newRadius) {
        if (newRadius == _radius)
            return;

        _radius = newRadius;

        for (auto object: objects()) {
            reinterpret_cast<DayItem*>(object)->setLightForce(lengthForce());
            reinterpret_cast<DayItem*>(object)->setRadius(_radius);

        }
    }

    /**
     * @brief axis This is sxis of rotation. all objects will be moving around this axis. The axis is general 3d vector object.
     * @return rotation axis.
     * @note By default it is y axis
     */
    const QVector3D &axis() const {
        return _axis;
    }

    /**
     * @brief setAxis This method sets new value of the rotation axis. For get more information see the axis method.
     * @param newAxis This is new value of the rotation axis.
     */
    void setAxis(const QVector3D &newAxis) {
        if (newAxis == _axis)
            return;

        _axis = newAxis;

        for (auto object: objects()) {
            reinterpret_cast<DayItem*>(object)->setAxis(_axis);
        }
    }

    /**
     * @brief dayLengthSec This method return length of the game day in real secs.
     * @note by default this value is 360 sec
     * @return length of the game day in real secs.
     */
    float dayLengthSec() const {
        return _dayLengthSec;
    }

    /**
     * @brief setDayLengthSec This method sets new value of the day length.
     * @param newDayLongSec This is new value of the day length.
     * @note For get more information see the dayLengthSec method.
     */
    void setDayLengthSec(float newDayLengthSec) {

        if (newDayLengthSec == _dayLengthSec)
            return;

        _dayLengthSec = newDayLengthSec;

        for (auto object: objects()) {
            reinterpret_cast<DayItem*>(object)->setAngularVelocity(lengthToSpeed(_dayLengthSec));
        }
    }

private:
    float lengthToSpeed(float length) const {
        return (2 * M_PI * radius()) / length;
    }

    float lengthForce() const {
#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
        return _radius * 0.1;
#else
        return _radius * 15;
#endif
    }

    int _radius = 1000;
    float _dayLengthSec = 360;
    QVector3D _axis = {1,0,0};
};

}
#endif // DAY_H
