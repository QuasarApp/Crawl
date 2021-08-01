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
class CRAWL_EXPORT ParticleEffect : public IWorldItem
{
    Q_OBJECT
    /**
     *  @brief enabled if enabled is set to false, this emitter will not emit any particles.
     *  Usually this is used to conditionally turn an emitter on or off. If you want to continue emitting burst,
     *  keep emitRate at 0 instead of toggling this to false. The default value is true.
    */
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

    /**
     * @brief emitRate This property defines the constant emitting rate in particles per second. For example, if the emitRate is 120 and system animates at 60 frames per second, 2 new particles are emitted at every frame.
     *  The default value is 0.
     */
    Q_PROPERTY(float emitRate READ emitRate WRITE setEmitRate NOTIFY emitRateChanged)

    /**
     * @brief depthBias Holds the depth bias of the emitter. Depth bias is added to the object distance from camera when sorting objects. This can be used to force rendering order between objects close to each other, that might otherwise be rendered in different order in different frames. Negative values cause the sorting value to move closer to the camera while positive values move it further from the camera.
     */
    Q_PROPERTY(float depthBias READ depthBias WRITE setDepthBias NOTIFY depthBiasChanged)

    /**
     * @brief lifeSpan This property defines the lifespan of a single particle in milliseconds.
     * The default value is 1000.
     * See also the lifeSpanVariation property.
     */
    Q_PROPERTY(int lifeSpan READ lifeSpan WRITE setLifeSpan NOTIFY lifeSpanChanged)

    /**
     * @brief lifeSpanVariation This property defines the lifespan variation of a single particle in milliseconds.
     * For example, to emit particles which will exist between 3 and 4 seconds:
     * @code
       lifeSpan: 3500
       lifeSpanVariation: 500
       @endcode
     * The default value is 0.
     */
    Q_PROPERTY(int lifeSpanVariation READ lifeSpanVariation WRITE setLifeSpanVariation NOTIFY lifeSpanVariationChanged)

    /**
     * @brief particleEndScale This property defines the scale multiplier of the particles at the end of particle lifeSpan.
     *  To have variation in the particle end sizes, use ParticleEffect::particleScaleVariation.
     *  When the value is negative, end scale is the same as the particleScale,
     *  so scale doesn't change during the particle lifeSpan.
     *  The default value is -1.0.
     *  See also ParticleEffect::particleScale and ParticleEffect::particleScaleVariation.
     */
    Q_PROPERTY(float particleEndScale READ particleEndScale WRITE setParticleEndScale NOTIFY particleEndScaleChanged)

    /**
     * @brief particleRotationVariation This property defines the rotation variation of the particles in the beginning. Rotation variation is defined as degrees in euler angles.
     *  For example, to emit particles in fully random rotations: Qt.vector3d(180, 180, 180)
     *  See also ParticleEffect::particleRotation.
     */
    Q_PROPERTY(QVector3D particleRotationVariation READ particleRotationVariation WRITE setParticleRotationVariation NOTIFY particleRotationVariationChanged)

    /**
     * @brief particleRotationVelocity This property defines the rotation velocity of the particles in the beginning.
     *  Rotation velocity is defined as degrees per second in euler angles.
     *  See also ParticleEffect::particleRotationVelocityVariation.
     */
    Q_PROPERTY(QVector3D particleRotationVelocity READ particleRotationVelocity WRITE setParticleRotationVelocity NOTIFY particleRotationVelocityChanged)

    /**
     * @brief particleRotationVelocityVariation This property defines the rotation velocity variation of the particles.
     *  Rotation velocity variation is defined as degrees per second in euler angles.
     *  For example, to emit particles in random rotations which have random rotation velocity between -100 and 100
     *  degrees per second into any directions:

        @code
             particleRotationVariation: Qt.vector3d(180, 180, 180)
             particleRotationVelocityVariation: Qt.vector3d(100, 100, 100)
        @endcode
     * See also ParticleEffect::particleRotationVelocity.
     */
    Q_PROPERTY(QVector3D particleRotationVelocityVariation READ particleRotationVelocityVariation WRITE setParticleRotationVelocityVariation NOTIFY particleRotationVelocityVariationChanged)

    /**
     * @brief particleScale This property defines the scale multiplier of the particles at the beginning.
     *  To have variation in the particle sizes, use particleScaleVariation.
     *  The default value is 1.0.
     *  See also ParticleEffect::particleEndScale and ParticleEffect::particleScaleVariation.
     */
    Q_PROPERTY(float particleScale READ particleScale WRITE setParticleScale NOTIFY particleScaleChanged)

    /**
     * @brief particleScaleVariation This property defines the scale variation of the particles.
     *  This variation is used for both particleScale and particleEndScale.
     *  For example, to emit particles which start at scale 0.5 - 1.5 and end at 2.5 - 3.5:
     *  @code
        particleScale: 1.0
        particleEndScale: 3.0
        particleScaleVariation: 0.5
        @endcode
     * The default value is 0.0.
     * See also ParticleEffect::particleScale and ParticleEffect::particleScaleVariation.
     */
    Q_PROPERTY(float particleScaleVariation READ particleScaleVariation WRITE setParticleScaleVariation NOTIFY particleScaleVariationChanged)

    /**
     * @brief velocity can be used to set a starting velocity for emitted particles. If velocity is not set, particles start motionless and velocity comes from affectors if they are used.
     * @note For the initialisation of this propertye use ParticleEffect::useTargetVelosity and ParticleEffect::useDirectionVelosity methods
    */
    Q_PROPERTY(QObject *velocity READ velocity NOTIFY velocityChanged)

    /**
     * @brief particleDelegate This is path yo the qml delegate file of the particle object.
     * @return path to delegate of the particle object.
     */
    Q_PROPERTY(QString particleDelegate READ particleDelegate WRITE setParticleDelegate NOTIFY particleDelegateChanged)

    /**
     * @brief particleShape This property defines optional shape for the emitting area.
     *  Shape is scaled, positioned and rotated based on the emitter node properties.
     *  When the Shape fill property is set to false,
     *  emitting happens only from the surface of the shape. When the shape is not defined, emitting is done from the center point of the emitter node.
    */
    Q_PROPERTY(QString particleShape READ particleShape WRITE setParticleShape NOTIFY particleShapeChanged)

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
     * @code
       lifeSpan: 3500
       lifeSpanVariation: 500
       @endcode
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

        @code
             particleRotationVariation: Qt.vector3d(180, 180, 180)
             particleRotationVelocityVariation: Qt.vector3d(100, 100, 100)
        @endcode
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
     *  @code
        particleScale: 1.0
        particleEndScale: 3.0
        particleScaleVariation: 0.5
        @endcode
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
     * @brief particleDelegate This is path yo the qml delegate file of the particle object.
     * @return path to delegate of the particle object.
     */
    const QString &particleDelegate() const;

    /**
     * @brief setParticleDelegate This method sets new value of the path to qml particle object.
     * @param newParticleDelegate This is new value of the path to particle object.
     */
    void setParticleDelegate(const QString &newParticleDelegate);

    /**
     * @brief velocity This property can be used to set a starting velocity for emitted particles. If velocity is not set, particles start motionless and velocity comes from affectors if they are used.
     * @return current value of the ParticleEffect::velocity property
     */
    QObject *velocity() const;

    /**
     * @brief brust This method emits count amount of particles from this emitter during the next duration milliseconds.
     *  The particles are emitted as if the emitter was at position but all other properties are the same.
     * @param count This is count of emited particles
     * @param duration This ducration of the emitting particles.
     * @param position This is position wher the emiter should emit particles.
     * @return
     */
    QVector3D brust(int count,
                    int duration,
                    const QVector3D& position) const;

    /**
     * @brief brust This method emits count amount of particles from this emitter during the next duration milliseconds.
     * @param count This is count of emited particles
     * @param duration This ducration of the emitting particles.
     * @return
     */
    QVector3D brust(int count,
                    int duration) const;

    /**
     * @brief brust This method emits count amount of particles from this emitter immediately.
     * @param count This is count of emited particles
     * @return
     */
    QVector3D brust(int count) const;

    /**
     * @brief particleShape The ParticleShape3D element supports shapes like Cube,
     *  Sphere and Cylinder for particles needs.
     *  For example, emitter can use shape property to emit particles from the shape area.
     *  Shapes don't have position, scale or rotation.
     *  Instead, they use parent node for these properties.
     * @return path to qml shape element.
     */
    const QString &particleShape() const;

    /**
     * @brief setParticleShape This method set new path to shape element
     * @param newParticleShape This is new value of the path to qml shape element.
     */
    void setParticleShape(const QString &newParticleShape);

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
     * @brief particleDelegateChanged This signal emited when the particleDelegate propertye changed.
     */
    void particleDelegateChanged();

    /**
     * @brief velocityChanged This signal emited when the velocity propertye changed.
     */
    void velocityChanged();

    /**
     * @brief particleShapeChanged This signal emited when the shape propertye changed.
     */
    void particleShapeChanged();

protected:

    /**
     * @brief useDirectionVelosity This method can be invoked a starting velocity for emitted particles. If velocity is not set, particles start motionless and velocity comes from affectors if they are used.
     * This element sets emitted particle velocity towards the target direction vector.
     *  The length of the direction vector is used as the velocity magnitude.
     *  For example, to emit particles towards some random direction within x: 50..150, y: -20..20, z: 0:
     *  @code
     *   velositydirection: Qt.vector3d(100, 0, 0)
         velositydirectionVariation: Qt.vector3d(50, 20, 0)
     *  @endcode
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
     * @code
         velosityposition: Qt.vector3d(100, 0, 0)
         velositynormalized: true
         velositymagnitude: 15.0
         velositymagnitudeVariation: 5.0

     * @endcode


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

    /**
     * @brief setVelocity This method sets new value of ParticleEffect::velocity property.
     * @param newVelocity This is new value of the ParticleEffect::velocity property.
     */
    void setVelocity(QObject *newVelocity);

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

    QObject* _velocity = nullptr;

    QString _particleDelegate;
    QString _particleShape;
};
}
#endif // PARTICLEEFFECT_H
