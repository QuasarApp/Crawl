//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef BASEMOTION_H
#define BASEMOTION_H

#include "Crawl/irender.h"

#include <QQuaternion>

namespace CRAWL {

class GuiObject;

/**
 * @brief The BaseMotion class contains base functions of the motion.
 * For Create your own motion alghoritm you need to override two methods:
 *  * renderPosition
 *  * renderRotation
 */
class CRAWL_EXPORT BaseMotion : public virtual IRender
{
public:
    BaseMotion();

    // IRender interface
public:
    void render(unsigned int tbfMsec);

    /**
     * @brief staticRotation This method retur nstatic rotation in quaternion. The static rotation rotate object to setted value independet then movable vector.
     * @return quterion of the static rotation
     */
    const QQuaternion &staticRotation() const;

    /**
     * @brief setStaticRotation This metho sets new value of the static rotation of this object.
     * @param newStaticRotation new value of the static rotation.
     * @note if you want use eilor angles then use the QQuaternion::fromEulerAngles method.
     * @note See the staticRotation method for get more information.
     */
    void setStaticRotation(const QQuaternion &newStaticRotation);

protected:

    /**
     * @brief renderRotation This method recalc raration for an @a object. The Default do nothing.
     * @param object This is provessing object. Usually @a an object is casted pointer of this to GuiObject type.
     * @param tbfMsec This is time betwin frames argument. soame as in the IRender::render function.
     */
    virtual void renderRotation(GuiObject* object, unsigned int tbfMsec) = 0;

    /**
     * @brief renderRotation This method recalc position for an @a object.
     * @param object This is provessing object. Usually @a an object is casted pointer of this to GuiObject type.
     * @param tbfMsec This is time betwin frames argument. soame as in the IRender::render function.
     */
    virtual void renderPosition(GuiObject* object, unsigned int tbfMsec) = 0;

private:

    QQuaternion _staticRotation = QQuaternion::fromEulerAngles(0,0,0);

};
}
#endif // BASEMOTION_H
