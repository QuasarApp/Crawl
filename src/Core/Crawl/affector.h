#ifndef AFFECTOR_H
#define AFFECTOR_H

#include "iworlditem.h"


namespace CRAWL {

/**
 * @brief The Affector class is an abstract base class of affectors like Gravity3D, Wander3D, and PointRotator3D. By default affectors affect all particles in the system,
 *  but this can be limited by defining the particles list.
 *  If the system has multiple affectors, the order of affectors may result in different outcome, as affectors are applied one after another.
 *
 *  For custumisation your own Affectors you need to change the templateView qml file for your own class.
 * @note For get more inforamtion about available qml affectors see the qt documentation [page](https://doc.qt.io/qt-6.1/qml-qtquick3d-particles3d-affector3d.html)

   **Example of qml view file**

   @code

    Attractor3D {

        property var model: null
        property int guiId: (model) ? model.guiId : -1;

        rotation: (model)? model.rotation: Qt.quaternion(0, 0, 0, 0)
        scale: (model)? model.size: Qt.vector3d(0, 0, 0);
        position: (model) ? model.position: Qt.vector3d(0,0,0);
        visible: (model)? model.visible: false

        enabled: (model)? model.enabled: false

        positionVariation: Qt.vector3d(50, 50, 50)
        duration: 3000
        durationVariation: 1000
    }

   @endcode
*/
class CRAWL_EXPORT Affector : public IWorldItem
{
    Q_OBJECT

    /**
     * @brief enabled if enabled is set to false, this affector will not alter any particles. Usually this is used to conditionally turn an affector on or off.
The default value is true.
     */
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    Affector(const QString& name,
             const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
             QObject *ptr = nullptr);

    /**
     * @brief enabled if enabled is set to false, this affector will not alter any particles. Usually this is used to conditionally turn an affector on or off.
The default value is true.
     * @return true if the Affector is enabled else false.
     */
    bool enabled() const;

    /**
     * @brief setEnabled This method  enable or disable the affector object.
     * @param newEnabled new value.
     */
    void setEnabled(bool newEnabled);

signals:
    /**
     * @brief enabledChanged This signal emited when the object change own enabled status.
     */
    void enabledChanged();

private:
    bool _enabled = true;
};
}

#endif // AFFECTOR_H
