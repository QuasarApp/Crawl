//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef VECTORDIRECTION_H
#define VECTORDIRECTION_H

#include "viewtemaplatemodel.h"
#include <QVector3D>
#include "global.h"

namespace CRAWL {

/**
 * @brief The VectorDirection class.
 * This element sets emitted particle velocity towards the target direction vector.
 *  The length of the direction vector is used as the velocity magnitude.
 *  For example, to emit particles towards some random direction within x: 50..150, y: -20..20, z: 0:
 *  @code
 *   VectorDirection {
         direction: Qt.vector3d(100, 0, 0)
         directionVariation: Qt.vector3d(50, 20, 0)
     }
    @endcode
 *
 * @note This class use the CrawlVectorDirection.qml template as a view temaplate.
 */
class CRAWL_EXPORT VectorDirection: public ViewTemaplateModel
{
    Q_OBJECT

    /**
     * @brief velosityDirection this property defines the direction for particles target.
     *  The default value is (0, 100, 0) (upwards on the y-axis).
     */
    Q_PROPERTY(QVector3D velosityDirection READ velosityDirection WRITE setVelosityDirection NOTIFY velosityDirectionChanged)

    /**
     * @brief velosityDirectionValatility This property defines the direction variation for particles target.
     *  The default value is (0, 0, 0) (no variation).
     */
    Q_PROPERTY(QVector3D velosityDirectionValatility READ velosityDirectionValatility WRITE setVelosityDirectionValatility NOTIFY velosityDirectionValatilityChanged)

public:
    VectorDirection(const QVector3D& direction = {},
                    const QVector3D& directionValatility = {},
                    QObject * parent = nullptr);

    /**
     * @brief velosityDirection this property defines the direction for particles target.
     *  The default value is (0, 100, 0) (upwards on the y-axis).
     * @return current value of the velosityDirection property
     */
    const QVector3D &velosityDirection() const;

    /**
     * @brief setVelosityDirection This method sets new value of the ParticleEffect::velosityDirection property.
     * @param newVelosityDirection This is a new value of the ParticleEffect::velosityDirection property
     * @note This property will be workd only after invoke the useDirectionVelosity method.
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
     * @note This property will be workd only after invoke the useDirectionVelosity method.
     */
    void setVelosityDirectionValatility(const QVector3D &newVelosityDirectionValatility);

signals:

    /**
     * @brief velosityDirectionChanged This signal emited when the velosityDirection property changed.
     */
    void velosityDirectionChanged();

    /**
     * @brief velosityDirectionValatilityChanged This signal emited when the velosityDirectionValatility property changed.
     */
    void velosityDirectionValatilityChanged();

private:

    QVector3D _velosityDirection = {};
    QVector3D _velosityDirectionValatility = {};
};
}
#endif // VECTORDIRECTION_H
