//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "clasteritem.h"

#ifndef IWORLDLIGHT_H
#define IWORLDLIGHT_H

namespace CRAWL {

/**
 * @brief The IWorldLight class Is base interaface of the light object.
 * Override this class for the create own light system for level.
 * You need to create own qml file with light.
 *
 * @note If you wnat to create a new qml file the you need to inherit from the Light.qml file.
 *
 * ### Integration on the world.
 * You need to add one object of this class in the IWorld::initWorldRules method.
 * **Example:**
 *
 * ```cpp
 * CRAWL::WorldRule *World::initWorldRules() {

    return new CRAWL::WorldRule {
        {0, {
                {registerObject<MyLightObject>(), 1},
            }
        },
        {1000, {
                {registerObject<MyLightObject>(), 1},
            }
        },
    };
}
 * ```
 *
 * For integration This object you world see the IWorld::initWorldRules method
 */
class CRAWL_EXPORT IWorldLight: public ClasterItem
{
    Q_OBJECT
    Q_PROPERTY(int lightForce READ lightForce WRITE setLightForce NOTIFY lightForceChanged)
    Q_PROPERTY(bool castsShadow READ castsShadow WRITE setCastsShadow NOTIFY castsShadowChanged)
    Q_PROPERTY(float shadowFactor READ shadowFactor WRITE setShadowFactor NOTIFY shadowFactorChanged)
    Q_PROPERTY(float shadowFilter READ shadowFilter WRITE setShadowFilter NOTIFY shadowFilterChanged)
    Q_PROPERTY(float shadowMapFar READ shadowMapFar WRITE setShadowMapFar NOTIFY shadowMapFarChanged)
    Q_PROPERTY(float shadowBias READ shadowBias WRITE setShadowBias NOTIFY shadowBiasChanged)

public:

    IWorldLight(const QString& name,
                const QString& viewTempalte = "qrc:/CrawlModule/Light.qml",
                QObject *ptr = nullptr);

    /**
     * @brief lightForce This method return light force
     * @return light force value.
     */
    int lightForce() const;

    /**
     * @brief setLightForce This method sets new value for the light force.
     * @param newLightForce this is new value of the light force.
     */
    void setLightForce(int newLightForce);

    /**
     * @brief castsShadow When this property is enabled, the light will cast shadows. The default value is false.
     * @return current value of the castsShadow property.
     */
    bool castsShadow() const;

    /**
     * @brief setCastsShadow This method sets new value of the castsShadow property. for get more information see the castsShadow method.
     * @param newCastsShadow this is new value of the castsShadow property.
     */
    void setCastsShadow(bool newCastsShadow);

    /**
     * @brief shadowFactor This property determines how dark the cast shadows should be. The value range is [0, 100], where 0 mean no shadows and 100 means the light is fully shadowed. The default value is 5.
     * @return current value of the shadow factor
     */
    float shadowFactor() const;

    /**
     * @brief setShadowFactor This method return current value of the shadow factor.
     * @param newShadowFactor This is new value of the shadow factor property.
     * @note for get more information see the shadowFactor method.
     */
    void setShadowFactor(float newShadowFactor);

    /**
     * @brief shadowFilter This property sets how much blur is applied to the shadows. The default value is 5.
     * @return current value of the shadow filter property.
     */
    float shadowFilter() const;

    /**
     * @brief setShadowFilter This method return current value of the shadow filter property.
     * @param newShadowFilter This is new value of the shadow filter property.
     * @note for get more information see the shadowFilter method.
     */
    void setShadowFilter(float newShadowFilter);

    /**
     * @brief shadowMapFar The property determines the maximum distance for the shadow map. Smaller values improve the precision and effects of the map. The default value is 5000.
     * @return current value of the shadow map far property.
     */
    float shadowMapFar() const;

    /**
     * @brief setShadowMapFar This method return current value of the shadow map far property.
     * @param newShadowMapFar This is new value of the shadow map far property.
     * @note for get more information see the shadowMapFar method.
     */
    void setShadowMapFar(float newShadowMapFar);

    /**
     * @brief shadowBias This property is used to tweak the shadowing effect when when objects are casting shadows on themselves. The value range is [-1.0, 1.0]. Generally value inside [-0.1, 0.1] is sufficient. The default value is 0.
     * @return current value of the shadow bias property.
     */
    float shadowBias() const;

    /**
     * @brief setShadowBias This method return current value of the shadow bias property.
     * @param newShadowBias This is new value of the shadow bias property.
     * @note for get more information see the shadowBias method.
     */
    void setShadowBias(float newShadowBias);

signals:

    /**
     * @brief lightForceChanged This signal emits when light force has changed.
     */
    void lightForceChanged();

    /**
     * @brief castsShadowChanged This signal emits when the castsShadow property has changed.
     */
    void castsShadowChanged();

    /**
     * @brief shadowFactorChanged This signal emits when the shadowFactor property has changed.
     */
    void shadowFactorChanged();

    /**
     * @brief shadowFilterChanged This signal emits when the shadowFilter property has changed.
     */
    void shadowFilterChanged();

    /**
     * @brief shadowMapFarChanged This signal emits when the shadowMapFar property has changed.
     */
    void shadowMapFarChanged();

    /**
     * @brief shadowBiasChanged This signal emits when the shadowBias property has changed.
     */
    void shadowBiasChanged();

private:
    int _lightForce = 100;
    bool _castsShadow = false;
    float _shadowFactor = 5;
    float _shadowFilter = 5;
    float _shadowMapFar = 5000;
    float _shadowBias = 0;
};
}
#endif // IWORLDLIGHT_H
