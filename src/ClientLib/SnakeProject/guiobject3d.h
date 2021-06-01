#ifndef GUIOBJECT3D_H
#define GUIOBJECT3D_H

#include "guiobject.h"

/**
 * @brief The GuiObject3D class This is 3d implementation of the Qt Quick 3d engine objects.
 */
class GuiObject3D : public GuiObject {
    Q_OBJECT

    Q_PROPERTY(double z READ z NOTIFY zChanged)
    Q_PROPERTY(double scaleZ READ scaleZ NOTIFY scaleZChanged)
    Q_PROPERTY(double scaleX READ scaleX NOTIFY hChanged)
    Q_PROPERTY(double scaleY READ scaleY NOTIFY wChanged)

    Q_PROPERTY(QString mash READ mash NOTIFY mashChanged)

public:
    GuiObject3D(const QString& viewTempalte = "GraphicItem", QObject *ptr = nullptr);

    /**
     * @brief z this is z axis
     * @return return z position of the object.
     */
    double z() const;

    /**
     * @brief scaleZ This is size object of the z axis.
     * @return return size of z axis
     */
    double scaleZ() const;

    /**
     * @brief mash This method return path to mash of the 3d object.
     * @return Path of the mash object.
     * @note for preparew mash use the obj file in Blender and convert obj files to mash using **balsam** tool.
     */
    QString mash() const;

    /**
     * @brief setZ This method sets new z point of object.
     * @param z this is new oint of z
     */
    void setZ(double z);

    /**
     * @brief setScaleZ This method sets new scale fcator of object.
     * @param scaleFactor new value of the scale factor.
     */
    void setScaleZ(double scaleFactor);

    /**
     * @brief setMash This method sets new path to mash object. For create mash object use the balsam tool.
     * @param mash This is path to mash object.
     */
    void setMash(const QString& mash);

    /**
     * @brief scaleX This method is simple wraper of the w property.
     * @return width of the object.
     */
    double scaleX() const;

    /**
     * @brief scaleY This metthod is simple wraper of the h proprty.
     * @return return height of the object.
     */
    double scaleY() const;

signals:
    /**
     * @brief zChanged This signal emmited when z point changed.
     */
    void zChanged();

    /**
     * @brief scaleZChanged This signale emited when sale factor of the z axis are changed.
     */
    void scaleZChanged();

    /**
     * @brief mashChanged
     */
    void mashChanged();

private:
    double _z = 0;
    double _scaleZ = 1;
    QString _mash = "#Cube";
};

#endif // GUIOBJECT3D_H
