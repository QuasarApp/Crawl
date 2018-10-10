#ifndef ITEMWORLD_H
#define ITEMWORLD_H


#include "guiobject.h"
#include <QString>

class ItemWorld : public GuiObject
{
private:    
    qint64 time;
    double *speed = nullptr;
    bool beckGroundObject = false;
protected:
    virtual void setSize(double x, double y);
    void setBeckGroundObject(bool value);

public:
    ItemWorld(double x, double y);

    void render();

    bool checkContact(const QRectF& riger);
    bool isBeckGroundObject();

    ~ItemWorld();
    void setSpeed(double *value);
};

#endif // ITEMWORLD_H
