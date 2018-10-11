#ifndef ITEMWORLD_H
#define ITEMWORLD_H

#include "guiobject.h"
#include <QString>

class ItemWorld : public GuiObject
{
private:    
    bool beckGroundObject = false;
protected:
    virtual void setSize(double x, double y);
    void setBeckGroundObject(bool value);

public:
    ItemWorld(double x, double y);

    void render();
    bool move(const QRectF& snakeRiger, double dx);
    bool isBeckGroundObject();

    ~ItemWorld();
};

#endif // ITEMWORLD_H
