//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "viewtemaplatemodel.h"
#include <QVector3D>
#include "global.h"

#ifndef TARGETDIRECTION_H
#define TARGETDIRECTION_H

namespace CRAWL {

/**
 * @brief The TargetDirection class.
 *  This element sets emitted particle velocity towards the target position.
 *  For example, to emit particles towards position (100, 0, 0) with random magnitude between 10..20:
 *  @code
    TargetDirection {
             position: Qt.vector3d(100, 0, 0)
             normalized: true
             magnitude: 15.0
             magnitudeVariation: 5.0
         }
     }
     @endcode

 * @note This class use the CrawlTargetDirection.qml template as a view temaplate.
 */
class CRAWL_EXPORT TargetDirection: public ViewTemaplateModel
{
    Q_OBJECT

    /**
     * @brief velosityMagnitude This property defines the magnitude in position change per second.
     *  Negative magnitude accelerates the opposite way from the position.
     *  When the normalized is false, this is multiplied with the distance to the target position.
     *  The default value is 1.0.
     */
    Q_PROPERTY(float velosityMagnitude READ velosityMagnitude WRITE setVelosityMagnitude NOTIFY velosityMagnitudeChanged)

    /**
     * @brief velosityMagnitudeVariation This property defines the magnitude variation in position change per second.
     *  When the normalized is false, this is multiplied with the distance to the target position.
     *  The default value is 0.0.
     */
    Q_PROPERTY(float velosityMagnitudeVariation READ velosityMagnitudeVariation WRITE setVelosityMagnitudeVariation NOTIFY velosityMagnitudeVariationChanged)

    /**
     * @brief velosityNormalized This property defines if the distance to position should be considered as normalized or not.
     *  When this is false, distance to the position affects the magnitude of the particles velocity.
     *  When set to true, distance is normalized and velocity amount comes only from magnitude and magnitudeVariation.
     *  The default value is false.
     */
    Q_PROPERTY(bool velosityNormalized READ velosityNormalized WRITE setVelosityNormalized NOTIFY velosityNormalizedChanged)

    /**
     * @brief velosityTargetPosition This property defines the position for particles target.
     *  The default value is (0, 0, 0) (the center of the emitter).
     */
    Q_PROPERTY(QVector3D velosityTargetPosition READ velosityTargetPosition WRITE setVelosityTargetPosition NOTIFY velosityTargetPositionChanged)

    /**
     * @brief velosityTargetPositionVariation This property defines the position variation for particles target.
     *  The default value is (0, 0, 0) (no variation).
     */
    Q_PROPERTY(QVector3D velosityTargetPositionVariation READ velosityTargetPositionVariation WRITE setVelosityTargetPositionVariation NOTIFY velosityTargetPositionVariationChanged)

public:
    TargetDirection(float velosityMagnitude = 1,
                    float velosityMagnitudeVariation = 0,
                    bool velosityNormalized = false,
                    const QVector3D& velosityTargetPosition = {0,0,0},
                    const QVector3D& velosityTargetPositionVariation = {0,0,0},
                    QObject * parent = nullptr);

    /**
     * @brief velosityMagnitude This property defines the magnitude in position change per second.
     *  Negative magnitude accelerates the opposite way from the position.
     *  When the normalized is false, this is multiplied with the distance to the target position.
     *  The default value is 1.0.
     * @return current value of the velosityMagnitude property
     */
    float velosityMagnitude() const;

    /**
     * @brief setVelosityMagnitude This method sets new value of the ParticleEffect::velosityMagnitude property.
     * @param newVelosityMagnitude This is a new value of the ParticleEffect::velosityMagnitude property
     * @note This propertye will be workd only after invoke the useTargetVelosity method.
     */
    void setVelosityMagnitude(float newVelosityMagnitude);

    /**
     * @brief velosityMagnitudeVariation This property defines the magnitude variation in position change per second.
     *  When the normalized is false, this is multiplied with the distance to the target position.
     *  The default value is 0.0.
     * @return current value of the velosityMagnitudeVariation property
     */
    float velosityMagnitudeVariation() const;

    /**
     * @brief setVelosityMagnitudeVariation This method sets new value of the ParticleEffect::velosityMagnitudeVariation property.
     * @param newVelosityMagnitudeVariation This is a new value of the ParticleEffect::velosityMagnitudeVariation property
     * @note This propertye will be workd only after invoke the useTargetVelosity method.
     */
    void setVelosityMagnitudeVariation(float newVelosityMagnitudeVariation);

    /**
     * @brief velosityNormalized This property defines if the distance to position should be considered as normalized or not.
     *  When this is false, distance to the position affects the magnitude of the particles velocity.
     *  When set to true, distance is normalized and velocity amount comes only from magnitude and magnitudeVariation.
     *  The default value is false.
     * @return current value of the velosityNormalized property
     */
    bool velosityNormalized() const;

    /**
     * @brief setVelosityNormalized This method sets new value of the ParticleEffect::velosityNormalized property.
     * @param newVelosityNormalized This is a new value of the ParticleEffect::velosityNormalized property
     * @note This propertye will be workd only after invoke the useTargetVelosity method.
     */
    void setVelosityNormalized(bool newVelosityNormalized);

    /**
     * @brief velosityTargetPosition This property defines the position for particles target.
     *  The default value is (0, 0, 0) (the center of the emitter).
     * @return current value of the velosityNormalized property
     */
    const QVector3D &velosityTargetPosition() const;

    /**
     * @brief setVelosityTargetPosition This method sets new value of the ParticleEffect::velosityTargetPosition property.
     * @param newVelosityTargetPosition This is a new value of the ParticleEffect::velosityTargetPosition property
     * @note This propertye will be workd only after invoke the useTargetVelosity method.
     */
    void setVelosityTargetPosition(const QVector3D &newVelosityTargetPosition);

    /**
     * @brief velosityTargetPositionVariation This property defines the position variation for particles target.
     *  The default value is (0, 0, 0) (no variation).
     * @return current value of the velosityTargetPositionVariation property
     */
    const QVector3D &velosityTargetPositionVariation() const;

    /**
     * @brief setVelosityTargetPositionVariation This method sets new value of the ParticleEffect::velosityTargetPositionVariation property.
     * @param newVelosityTargetPositionVariation This is a new value of the ParticleEffect::velosityTargetPositionVariation property
     * @note This propertye will be workd only after invoke the useTargetVelosity method.
     */
    void setVelosityTargetPositionVariation(const QVector3D &newVelosityTargetPositionVariation);

signals:

    /**
     * @brief velosityMagnitudeChanged This signal emited when the velosityMagnitude propertye changed.
     */
    void velosityMagnitudeChanged();

    /**
     * @brief velosityMagnitudeVariationChanged This signal emited when the velosityMagnitudeVariation propertye changed.
     */
    void velosityMagnitudeVariationChanged();

    /**
     * @brief velosityNormalizedChanged This signal emited when the velosityNormalized propertye changed.
     */
    void velosityNormalizedChanged();

    /**
     * @brief velosityTargetPositionChanged This signal emited when the velosityTargetPosition propertye changed.
     */
    void velosityTargetPositionChanged();

    /**
     * @brief velosityTargetPositionVariationChanged This signal emited when the velosityTargetPositionVariation propertye changed.
     */
    void velosityTargetPositionVariationChanged();

private:
    float _velosityMagnitude = 1;
    float _velosityMagnitudeVariation = 0;
    bool _velosityNormalized = false;
    QVector3D _velosityTargetPosition = {};
    QVector3D _velosityTargetPositionVariation = {};
};

}
#endif // TARGETDIRECTION_H
