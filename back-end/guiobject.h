#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include "baseclass.h"
#include "QObject"

class GuiObject:public QObject, public BaseClass
{
    Q_OBJECT
private:
    void generateId();
protected:
    double x, y, angle;
    int id;
    QString texture;
    double sizeX, sizeY, radius;

    void setTexture(const QString &texture);
public:
    GuiObject(QObject *ptr = nullptr);

    double getAngle() const;
    void setAngle(double angle);

    double getY() const;
    void setY(double y);

    double getX() const;
    void setX(double x);


    QString getTexture() const;
    int getId() const;
    double getSizeX() const;
    double getSizeY() const;
};

#endif // GUIOBJECT_H
