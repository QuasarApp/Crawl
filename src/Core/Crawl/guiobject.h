//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include "QObject"

#include <QQuaternion>
#include <QRectF>
#include <QVector3D>
#include "Crawl/irender.h"

#define DEFAULT_VIEW_TEMPLATE "qrc:/CrawlModule/GraphicItem.qml"
/** the AUTO_CLASS_NAME define gets name from the class and namespace.
 */
#define AUTO_CLASS_NAME typeid(this).name()

namespace CRAWL {


/**
 * @brief The GuiObject class This base model for gui objects.
 *
 * # Overriding Own gui objects.
 *
 * The gui objct contains base properties for drow objects on scane
 * * position
 * * ratation
 * * mash
 * * and map textures
 *
 * All properies implemented on the GraphicItem.qml file.
 *
 * If you want to change view for your own object then you need to ooverride the GuiObject::viewTemplate property and create a own qml file for view your changes.
 *
 * ### Example:
 *
 * Create a new qml file **OwnView.qml**
 * ```qml
 *  import CrawlModule 1.0
 *
 *  GraphicItem {
 *      // your own implementation
 *  }
 * ```
 *
 * Override property in cpp object.
 *
 * ```cpp
 * class MyObject: public IWorldItem {
 *     MyObject(): IWorldItem("name", "qrc:/path/to/OwnView.qml") {
 *     }
 * }
 * ```
 */
class CRAWL_EXPORT GuiObject: public QObject, virtual public IRender {
    Q_OBJECT
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int guiId READ guiId NOTIFY guiIdChanged)
    Q_PROPERTY(QString viewTemplate READ viewTemplate NOTIFY viewTemplateChanged)

    Q_PROPERTY(QVector3D position READ position WRITE setposition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QQuaternion ratation READ ratation WRITE setRatation NOTIFY ratationChanged)

    Q_PROPERTY(QString mash READ mash WRITE setMash NOTIFY mashChanged)

    // textures
    Q_PROPERTY(QString baseColorMap READ baseColorMap NOTIFY baseColorMapChanged)
    Q_PROPERTY(QString roughnessMap READ roughnessMap NOTIFY roughnessMapChanged)
    Q_PROPERTY(QString normalMap READ normalMap NOTIFY normalMapChanged)
    Q_PROPERTY(QString emissiveMap READ emissiveMap NOTIFY emissiveMapChanged)


public:
    GuiObject(const QString& name,
              const QString& viewTempalte = DEFAULT_VIEW_TEMPLATE,
              QObject *ptr = nullptr);

    const QString &color() const;
    void setColor(const QString &color);

    virtual void reset();
    QString viewTemplate() const;

    int guiId() const;
    void setGuiId(int guiId);

    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);

    void setDx(float newDx);
    void setDy(float newDy);
    void setDz(float newDz);

    const QString &baseColorMap() const;
    const QString &roughnessMap() const;
    const QString &normalMap() const;
    const QString &emissiveMap() const;

    /**
     * @brief center This method return center of object
     * @return 3d point of the object center.
     * @warning This method calc center in runtime.
     */
    QVector3D center() const;

    /**
     * @brief intersects This method check if this object contains @a point object.
     * @param point This is checked point
     * @return true if the point contains in the object cube.
     * @warning This functions check intersect approximate and only works correctly for cubic objects. if you try compare plane objects or lines you get incorrect results.
     */
    bool intersects(const QVector3D& point) const;

    /**
     * @brief intersects This method check intersects betwin current object and @a object.
     * @param object This is input object.
     * @return true if the two objects has common points.
     * @warning This functions check intersect approximate and only works correctly for cubic objects. if you try compare plane objects or lines you get incorrect results.
     */
    bool intersects(const GuiObject& object) const;

    const QVector3D &position() const;
    void setposition(const QVector3D &newposition);

    const QVector3D &size() const;
    void setSize(const QVector3D &newSize);

    const QQuaternion &ratation() const;
    void setRatation(const QQuaternion &newRatation);

    const QString &mash() const;
    void setMash(const QString &newMash);

    /**
     * @brief className This method return class name.
     * The class name using as a group of objects on thw world.
     * @return class name;
     * @note the class name should be sets on the consturctor of child classes of this class.
     */
    const QString &className() const;

    /**
     * @brief visible This property sets to true if object visibel else false.
     * @return true if object is visible
     */
    bool visible() const;

    /**
     * @brief setVisible This method sets new vlaue of the visible property
     * @param newVisible new value of visible
     */
    void setVisible(bool newVisible);

signals:
    void guiIdChanged(int guiId);
    void colorChanged(QString color);
    void viewTemplateChanged(QString viewTemplate);

    void baseColorMapChanged();
    void roughnessMapChanged();
    void normalMapChanged();
    void emissiveMapChanged();

    void positionChanged();
    void sizeChanged();
    void ratationChanged();

    void mashChanged();

    void visibleChanged();

protected:

    /**
     * @brief setBaseColorMap This method sets path to the base color map of the object. See the baseColorMap method for get more information.
     * @param baseColorMap This is new value of the path to base color map.
     */
    void setBaseColorMap(const QString& baseColorMap);

    /**
     * @brief setRoughnessMap This method sets path to the roughness map of the object. See the roughnessMap method for get more information.
     * @param roughnessMap This is new value of the path to roughness map.
     */
    void setRoughnessMap(const QString& roughnessMap);

    /**
     * @brief setNormalMap This method sets path to the normal map of the object. See the normalMap method for get more information.
     * @param normalMap This is new value of the path to normal map.
     */
    void setNormalMap(const QString& normalMap);

    /**
     * @brief setEmissiveMap This method sets path to the emissive map of the object. See the emissiveMap method for get more information.
     * @param emissiveMap This is new value of the path to emissive map.
     */
    void setEmissiveMap(const QString& emissiveMap);

private:
    void generateId();

    int _guiId = -1;
    QString _color = "#ff1111";

    QString _baseColorMap;
    QString _roughnessMap;
    QString _normalMap;
    QString _emissiveMap;
    QString _viewTemplate;

    QVector3D _position;
    QVector3D _size;
    QQuaternion _ratation;
    QString _mash;
    QString _className;
    bool _visible = true;
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
};

}
#endif // GUIOBJECT_H
