#ifndef ITEMWORLD_H
#define ITEMWORLD_H

#include "guiobject.h"
#include <QString>

class ItemWorld : public GuiObject
{
private:    
    bool beckGroundObject = false;
protected:
    virtual void setSize(double h, double w);
    virtual void setLoc(double x, double y);
    void setBeckGroundObject(bool value);

public:
    ItemWorld(double x, double y, const QString& GuiTemplate = "GraphicItem");

    void render() override;
    virtual bool move(const GuiObject* snakeRiger, double dx);
    bool isBeckGroundObject();

    ~ItemWorld();
};

#endif // ITEMWORLD_H
