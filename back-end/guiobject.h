#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include "baseclass.h"
#include "QObject"

class GuiObject:public QObject, public BaseClass
{
    Q_OBJECT
protected:
    double x, y, angle;
    QString texture;
    double sizeX, sizeY, radius;
public:
    GuiObject(QObject *ptr = nullptr);

    double getAngle() const;
    void setAngle(double angle);

    double getY() const;
    void setY(double y);

    double getX() const;
    void setX(double x);

    QString getTexture() const;
    void setTexture(const QString &texture);
};

#endif // GUIOBJECT_H
