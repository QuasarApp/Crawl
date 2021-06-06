#ifndef ITEMWORLD_H
#define ITEMWORLD_H

#include "guiobject.h"
#include <QString>

class ItemWorld : public GuiObject
{
    Q_OBJECT
public:
    ItemWorld(double x, double y, const QString& GuiTemplate = "GraphicItem");

    void render() override;
    virtual bool move(const GuiObject* snakeRiger, double dx);
    bool isBeckGroundObject();

    ~ItemWorld();


protected:
    void setSize(double h, double w);
    void setLoc(double x, double y);
    void setBeckGroundObject(bool value);


private:
    bool beckGroundObject = false;
};

#endif // ITEMWORLD_H
