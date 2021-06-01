#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include "baseclass.h"
#include "QObject"

#include <QRectF>

class GuiObject:public QObject, public BaseClass
{
    Q_OBJECT
// @todo: add color
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int guiId READ guiId NOTIFY guiIdChanged)
    Q_PROPERTY(QString viewTemplate READ viewTemplate NOTIFY viewTemplateChanged)

    Q_PROPERTY(float x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(float y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(float z READ z WRITE setZ NOTIFY zChanged)

// size of object for each axis
    Q_PROPERTY(float dx READ dx WRITE setDx NOTIFY dxChanged)
    Q_PROPERTY(float dy READ dy WRITE setDy NOTIFY dyChanged)
    Q_PROPERTY(float dz READ dz WRITE setDz NOTIFY dzChanged)

// rotation foeach axis
    Q_PROPERTY(float rx READ rx WRITE setRx NOTIFY rxChanged)
    Q_PROPERTY(float ry READ ry WRITE setRy NOTIFY ryChanged)
    Q_PROPERTY(float rz READ rz WRITE setRz NOTIFY rzChanged)

    // textures
    Q_PROPERTY(QString baseColorMap READ baseColorMap NOTIFY baseColorMapChanged)
    Q_PROPERTY(QString roughnessMap READ roughnessMap NOTIFY roughnessMapChanged)
    Q_PROPERTY(QString normalMap READ normalMap NOTIFY normalMapChanged)
    Q_PROPERTY(QString emissiveMap READ emissiveMap NOTIFY emissiveMapChanged)


public:
    GuiObject(const QString& viewTempalte = "GraphicItem", QObject *ptr = nullptr);

    void render() override;

    QString color() const;
    void setColor(QString color);

    virtual void reset();
    QString viewTemplate() const;

    int guiId() const;
    void setGuiId(int guiId);

    float x() const;
    void setX(float newX);

    float y() const;
    void setY(float newY);

    float z() const;
    void setZ(float newZ);

    float dx() const;
    void setDx(float newDx);

    float dy() const;
    void setDy(float newDy);

    float dz() const;
    void setDz(float newDz);

    float rx() const;
    void setRx(float newRx);

    float ry() const;
    void setRy(float newRy);

    float rz() const;
    void setRz(float newRz);

    const QString &baseColorMap() const;

    const QString &roughnessMap() const;

    const QString &normalMap() const;

    const QString &emissiveMap() const;

public slots:

    void setRadius(int radius);

signals:
    void guiIdChanged(int guiId);
    void colorChanged(QString color);
    void viewTemplateChanged(QString viewTemplate);

    void xChanged();
    void yChanged();
    void zChanged();
    void dxChanged();
    void dyChanged();
    void dzChanged();
    void rxChanged();
    void ryChanged();
    void rzChanged();
    void baseColorMapChanged();
    void roughnessMapChanged();
    void normalMapChanged();
    void emissiveMapChanged();

protected:
    int _guiId = -1;
    QString _color = "";

    float _x;
    float _y;
    float _z;
    float _dx;
    float _dy;
    float _dz;
    float _rx;
    float _ry;
    float _rz;

    void setTexture(const QString &texture);

private:
    void generateId();


    QString _baseColorMap;
    QString _roughnessMap;
    QString _normalMap;
    QString _emissiveMap;
    QString _viewTemplate;

};

#endif // GUIOBJECT_H
