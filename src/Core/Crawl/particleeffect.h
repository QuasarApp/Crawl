//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include "iworlditem.h"

namespace CRAWL {

/**
 * @brief The ParticleEffect class This element emits logical particles into the ParticleSystem, with the given starting attributes.
At least one emitter is required to have particles in the ParticleSystem3D.
    Please see the [qt](https://doc.qt.io/qt-6/qtquick3d-index.html) documentation for get more inforamtion
 */
class ParticleEffect : public IWorldItem
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(float emitRate READ emitRate WRITE setEmitRate NOTIFY emitRateChanged)
    Q_PROPERTY(float depthBias READ depthBias WRITE setDepthBias NOTIFY depthBiasChanged)
    Q_PROPERTY(int lifeSpan READ lifeSpan WRITE setLifeSpan NOTIFY lifeSpanChanged)
    Q_PROPERTY(int lifeSpanVariation READ lifeSpanVariation WRITE setLifeSpanVariation NOTIFY lifeSpanVariationChanged)
    Q_PROPERTY(float particleEndScale READ particleEndScale WRITE setParticleEndScale NOTIFY particleEndScaleChanged)
    Q_PROPERTY(QVector3D particleRotationVariation READ particleRotationVariation WRITE setParticleRotationVariation NOTIFY particleRotationVariationChanged)
    Q_PROPERTY(QVector3D particleRotationVelocity READ particleRotationVelocity WRITE setParticleRotationVelocity NOTIFY particleRotationVelocityChanged)
    Q_PROPERTY(QVector3D particleRotationVelocityVariation READ particleRotationVelocityVariation WRITE setParticleRotationVelocityVariation NOTIFY particleRotationVelocityVariationChanged)
    Q_PROPERTY(float particleScale READ particleScale WRITE setParticleScale NOTIFY particleScaleChanged)
    Q_PROPERTY(float particleScaleVariation READ particleScaleVariation WRITE setParticleScaleVariation NOTIFY particleScaleVariationChanged)
    Q_PROPERTY(QVector3D velosityDirection READ velosityDirection WRITE setVelosityDirection NOTIFY velosityDirectionChanged)
    Q_PROPERTY(QVector3D velosityDirectionValatility READ velosityDirectionValatility WRITE setVelosityDirectionValatility NOTIFY velosityDirectionValatilityChanged)
    Q_PROPERTY(float velosityMagnitude READ velosityMagnitude WRITE setVelosityMagnitude NOTIFY velosityMagnitudeChanged)
    Q_PROPERTY(float velosityMagnitudeVariation READ velosityMagnitudeVariation WRITE setVelosityMagnitudeVariation NOTIFY velosityMagnitudeVariationChanged)
    Q_PROPERTY(bool velosityNormalized READ velosityNormalized WRITE setVelosityNormalized NOTIFY velosityNormalizedChanged)
    Q_PROPERTY(QVector3D velosityTargetPosition READ velosityTargetPosition WRITE setVelosityTargetPosition NOTIFY velosityTargetPositionChanged)
    Q_PROPERTY(QVector3D velosityTargetPositionVariation READ velosityTargetPositionVariation WRITE setVelosityTargetPositionVariation NOTIFY velosityTargetPositionVariationChanged)
    Q_PROPERTY(QString particleDelegate READ particleDelegate WRITE setParticleDelegate NOTIFY particleDelegateChanged)

public:
    ParticleEffect(const QString& name,
                   const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
                   QObject *ptr = nullptr);

    /**
     * @brief enabled if enabled is set to false, this emitter will not emit any particles.
     *  Usually this is used to conditionally turn an emitter on or off. If you want to continue emitting burst,
     *  keep emitRate at 0 instead of toggling this to false. The default value is true.
     * @return true if this effect is enabled.
     */
    bool enabled() const;

    /**
     * @brief setEnabled This method sets new value of the ParticleEffect::enabled property.
     * @param newEnabled This is a new value of the ParticleEffect::enabled property
     */
    void setEnabled(bool newEnabled);

    /**
     * @brief emitRate This property defines the constant emitting rate in particles per second. For example, if the emitRate is 120 and system animates at 60 frames per second, 2 new particles are emitted at every frame.
     *  The default value is 0.
     * @return current value of the emitRate property
     */
    float emitRate() const;

    /**
     * @brief setEmitRate This method sets new value of the ParticleEffect::emitRate property.
     * @param newEmitRate This is a new value of the ParticleEffect::emitRate property
     */
    void setEmitRate(float newEmitRate);

    /**
     * @brief depthBias Holds the depth bias of the emitter. Depth bias is added to the object distance from camera when sorting objects. This can be used to force rendering order between objects close to each other, that might otherwise be rendered in different order in different frames. Negative values cause the sorting value to move closer to the camera while positive values move it further from the camera.
     * @return current value of the depthBias property
     */
    float depthBias() const;

    /**
     * @brief setDepthBias This method sets new value of the ParticleEffect::depthBias property.
     * @param newDepthBias This is a new value of the ParticleEffect::depthBias property
     */
    void setDepthBias(float newDepthBias);

    /**
     * @brief lifeSpan This property defines the lifespan of a single particle in milliseconds.
     * The default value is 1000.
     * See also the lifeSpanVariation property.
     * @return current value of the lifeSpan property
     */
    int lifeSpan() const;

    /**
     * @brief setLifeSpan This method sets new value of the ParticleEffect::lifeSpan property.
     * @param newLifeSpan This is a new value of the ParticleEffect::lifeSpan property
     */
    void setLifeSpan(int newLifeSpan);

    /**
     * @brief lifeSpanVariation This property defines the lifespan variation of a single particle in milliseconds.
     * For example, to emit particles which will exist between 3 and 4 seconds:
     *
     * ```
       lifeSpan: 3500
       lifeSpanVariation: 500
       ```
     * The default value is 0.
     * @return current value of the lifeSpanVariation property
     */
    int lifeSpanVariation() const;

    /**
     * @brief setLifeSpanVariation This method sets new value of the ParticleEffect::lifeSpanVariation property.
     * @param newLifeSpanVariation This is a new value of the ParticleEffect::lifeSpanVariation property
     */
    void setLifeSpanVariation(int newLifeSpanVariation);

    /**
     * @brief particleEndScale This property defines the scale multiplier of the particles at the end of particle lifeSpan.
     *  To have variation in the particle end sizes, use ParticleEffect::particleScaleVariation.
     *  When the value is negative, end scale is the same as the particleScale,
     *  so scale doesn't change during the particle lifeSpan.
     *  The default value is -1.0.
     *  See also ParticleEffect::particleScale and ParticleEffect::particleScaleVariation.
     * @return current value of the particleEndScale property
     */
    float particleEndScale() const;

    /**
     * @brief setParticleEndScale This method sets new value of the ParticleEffect::particleEndScale property.
     * @param newParticleEndScale This is a new value of the ParticleEffect::particleEndScale property
     */
    void setParticleEndScale(float newParticleEndScale);

    /**
     * @brief particleRotationVariation This property defines the rotation variation of the particles in the beginning. Rotation variation is defined as degrees in euler angles.
     *  For example, to emit particles in fully random rotations: Qt.vector3d(180, 180, 180)
     *  See also ParticleEffect::particleRotation.
     * @return current value of the particleRotationVariation property
     */
    const QVector3D &particleRotationVariation() const;

    /**
     * @brief setParticleRotationVariation This method sets new value of the ParticleEffect::particleRotationVariation property.
     * @param newParticleRotationVariation This is a new value of the ParticleEffect::particleRotationVariation property
     */
    void setParticleRotationVariation(const QVector3D &newParticleRotationVariation);

    /**
     * @brief particleRotationVelocity This property defines the rotation velocity of the particles in the beginning.
     *  Rotation velocity is defined as degrees per second in euler angles.
     *  See also ParticleEffect::particleRotationVelocityVariation.
     * @return current value of the particleRotationVelocity property
     */
    const QVector3D &particleRotationVelocity() const;

    /**
     * @brief setParticleRotationVelocity This method sets new value of the ParticleEffect::particleRotationVelocity property.
     * @param newParticleRotationVelocity This is a new value of the ParticleEffect::particleRotationVelocity property
     */
    void setParticleRotationVelocity(const QVector3D &newParticleRotationVelocity);

    /**
     * @brief particleRotationVelocityVariation This property defines the rotation velocity variation of the particles.
     *  Rotation velocity variation is defined as degrees per second in euler angles.
     *  For example, to emit particles in random rotations which have random rotation velocity between -100 and 100
     *  degrees per second into any directions:

        ```
             particleRotationVariation: Qt.vector3d(180, 180, 180)
             particleRotationVelocityVariation: Qt.vector3d(100, 100, 100)
        ```
     * See also ParticleEffect::particleRotationVelocity.
     * @return current value of the particleRotationVelocityVariation property
     */
    const QVector3D &particleRotationVelocityVariation() const;

    /**
     * @brief setParticleRotationVelocityVariation This method sets new value of the ParticleEffect::particleRotationVelocityVariation property.
     * @param newParticleRotationVelocityVariation This is a new value of the ParticleEffect::particleRotationVelocityVariation property
     */
    void setParticleRotationVelocityVariation(const QVector3D &newParticleRotationVelocityVariation);

    /**
     * @brief particleScale This property defines the scale multiplier of the particles at the beginning.
     *  To have variation in the particle sizes, use particleScaleVariation.
     *  The default value is 1.0.
     *  See also ParticleEffect::particleEndScale and ParticleEffect::particleScaleVariation.
     * @return current value of the particleScale property
     */
    float particleScale() const;

    /**
     * @brief setParticleScale This method sets new value of the ParticleEffect::particleScale property.
     * @param newParticleScale This is a new value of the ParticleEffect::particleScale property
     */
    void setParticleScale(float newParticleScale);

    /**
     * @brief particleScaleVariation This property defines the scale variation of the particles.
     *  This variation is used for both particleScale and particleEndScale.
     *  For example, to emit particles which start at scale 0.5 - 1.5 and end at 2.5 - 3.5:
     *  ```
            particleScale: 1.0
            particleEndScale: 3.0
            particleScaleVariation: 0.5
        ```
     * The default value is 0.0.
     * See also ParticleEffect::particleScale and ParticleEffect::particleScaleVariation.
     * @return current value of the ParticleEffect::particleScaleVariation property
     */
    float particleScaleVariation() const;

    /**
     * @brief setParticleScaleVariation This method sets new value of the ParticleEffect::particleScaleVariation property.
     * @param newParticleScaleVariation This is a new value of the ParticleEffect::particleScaleVariation property
     */
    void setParticleScaleVariation(float newParticleScaleVariation);

    /**
     * @brief velosityDirection this property defines the direction for particles target.
     *  The default value is (0, 100, 0) (upwards on the y-axis).
     * @return current value of the velosityDirection property
     */
    const QVector3D &velosityDirection() const;

    /**
     * @brief setVelosityDirection This method sets new value of the ParticleEffect::velosityDirection property.
     * @param newVelosityDirection This is a new value of the ParticleEffect::velosityDirection property
     * @note This propertye will be workd only after invoke the useDirectionVelosity method.
     */
    void setVelosityDirection(const QVector3D &newVelosityDirection);

    /**
     * @brief velosityDirectionValatility This property defines the direction variation for particles target.
     *  The default value is (0, 0, 0) (no variation).
     * @return current value of the velosityDirectionValatility property
     */
    const QVector3D &velosityDirectionValatility() const;

    /**
     * @brief setVelosityDirectionValatility This method sets new value of the ParticleEffect::velosityDirectionValatility property.
     * @param newVelosityDirectionValatility This is a new value of the ParticleEffect::velosityDirectionValatility property
     * @note This propertye will be workd only after invoke the useDirectionVelosity method.
     */
    void setVelosityDirectionValatility(const QVector3D &newVelosityDirectionValatility);

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

    /**
     * @brief particleDelegate This is path yo the qml delegate file of the particle object.
     * @return path to delegate of the particle object.
     */
    const QString &particleDelegate() const;

    /**
     * @brief setParticleDelegate This method sets new value of the path to qml particle object.
     * @param newParticleDelegate This is new value of the path to particle object.
     */
    void setParticleDelegate(const QString &newParticleDelegate);

signals:

    /**
     * @brief enabledChanged This signal emited when the enabled propertye changed.
     */
    void enabledChanged();

    /**
     * @brief emitRateChanged This signal emited when the emitRate propertye changed.
     */
    void emitRateChanged();

    /**
     * @brief depthBiasChanged This signal emited when the depthBias propertye changed.
     */
    void depthBiasChanged();

    /**
     * @brief lifeSpanChanged This signal emited when the lifeSpan propertye changed.
     */
    void lifeSpanChanged();

    /**
     * @brief lifeSpanVariationChanged This signal emited when the ifeSpanVariation propertye changed.
     */
    void lifeSpanVariationChanged();

    /**
     * @brief particleEndScaleChanged This signal emited when the particleEndScale propertye changed.
     */
    void particleEndScaleChanged();

    /**
     * @brief particleRotationVariationChanged This signal emited when the particleRotationVariation propertye changed.
     */
    void particleRotationVariationChanged();

    /**
     * @brief particleRotationVelocityChanged This signal emited when the particleRotationVelocity propertye changed.
     */
    void particleRotationVelocityChanged();

    /**
     * @brief particleRotationVelocityVariationChanged This signal emited when the particleRotationVelocityVariation propertye changed.
     */
    void particleRotationVelocityVariationChanged();

    /**
     * @brief particleScaleChanged This signal emited when the particleScale propertye changed.
     */
    void particleScaleChanged();

    /**
     * @brief particleScaleVariationChanged This signal emited when the particleScaleVariation propertye changed.
     */
    void particleScaleVariationChanged();

    /**
     * @brief velosityDirectionChanged This signal emited when the velosityDirection propertye changed.
     */
    void velosityDirectionChanged();

    /**
     * @brief velosityDirectionValatilityChanged This signal emited when the velosityDirectionValatility propertye changed.
     */
    void velosityDirectionValatilityChanged();

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

    /**
     * @brief particleDelegateChanged This signal emited when the particleDelegate propertye changed.
     */
    void particleDelegateChanged();

protected:

    /**
     * @brief useDirectionVelosity This method can be invoked a starting velocity for emitted particles. If velocity is not set, particles start motionless and velocity comes from affectors if they are used.
     * This element sets emitted particle velocity towards the target direction vector.
     *  The length of the direction vector is used as the velocity magnitude.
     *  For example, to emit particles towards some random direction within x: 50..150, y: -20..20, z: 0:
     *  ```
     *   velositydirection: Qt.vector3d(100, 0, 0)
         velositydirectionVariation: Qt.vector3d(50, 20, 0)
     *  ```
     * @param velosityDirection see the ParticleEffect::velosityDirection property
     * @param velosityDirectionValatility see the ParticleEffect::velosityDirectionValatility property
     * @note This and useTargetVelosity method is not compatible. If you invoke them together then will works correctly will be only last invoked method.
     */
    void useDirectionVelosity(const QVector3D& velosityDirection,
                              const QVector3D& velosityDirectionValatility = {});

    /**
     * @brief useTargetVelosity This method can be invoked a starting velocity for emitted particles. If velocity is not set, particles start motionless and velocity comes from affectors if they are used.
     * This element sets emitted particle velocity towards the target position.
     * For example, to emit particles towards position (100, 0, 0) with random magnitude between 10..20:
     * ```
         velosityposition: Qt.vector3d(100, 0, 0)
         velositynormalized: true
         velositymagnitude: 15.0
         velositymagnitudeVariation: 5.0

     * ```


     * @param velosityMagnitude see the ParticleEffect::velosityMagnitude property
     * @param velosityMagnitudeVariation see the ParticleEffect::velosityMagnitudeVariation property
     * @param velosityNormalized see the ParticleEffect::velosityNormalized property
     * @param velosityTargetPosition see the ParticleEffect::velosityTargetPosition property
     * @param velosityTargetPositionVariation see the ParticleEffect::velosityTargetPositionVariation property
     * @note This and useDirectionVelosity method is not compatible. If you invoke them together then will works correctly will be only last invoked method.
     */
    void useTargetVelosity(float velosityMagnitude,
                           float velosityMagnitudeVariation,
                           bool velosityNormalized,
                           const QVector3D& velosityTargetPosition,
                           const QVector3D& velosityTargetPositionVariation);
private:
    bool _enabled = false;
    float _emitRate = 0;
    float _depthBias = 0;
    int _lifeSpan = 1000;
    int _lifeSpanVariation = 0;
    float _particleEndScale = -1.0;
    QVector3D _particleRotationVariation = {};
    QVector3D _particleRotationVelocity = {};
    QVector3D _particleRotationVelocityVariation = {};
    float _particleScale = 1;
    float _particleScaleVariation = 0;

    // velosity
    QVector3D _velosityDirection = {};
    QVector3D _velosityDirectionValatility = {};

    float _velosityMagnitude = 1;
    float _velosityMagnitudeVariation = 0;
    bool _velosityNormalized = false;
    QVector3D _velosityTargetPosition = {};
    QVector3D _velosityTargetPositionVariation = {};

    QString _particleDelegate;
};
}
#endif // PARTICLEEFFECT_H
