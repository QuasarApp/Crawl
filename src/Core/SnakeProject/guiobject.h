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
#include "SnakeProject/irender.h"

/**
 * @brief The GuiObject class This base model for gui objects.
 */
class SNAKEPROJECT_EXPORT GuiObject: public QObject, public IRender {
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
    GuiObject(const QString& viewTempalte = ":/SnakeProjectModule/GraphicItem.qml", QObject *ptr = nullptr);

    QString color() const;
    void setColor(QString color);

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

protected:
    int _guiId = -1;
    QString _color = "";


private:
    void generateId();

    QString _baseColorMap;
    QString _roughnessMap;
    QString _normalMap;
    QString _emissiveMap;
    QString _viewTemplate;

    QVector3D _position;
    QVector3D _size;
    QQuaternion _ratation;
    QString _mash;
};

#endif // GUIOBJECT_H
