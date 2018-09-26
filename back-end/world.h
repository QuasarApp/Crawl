#ifndef WORLD_H
#define WORLD_H

#define SPEEDWORLD 10

#include <QVector>
#include "itemworld.h"
#include "baseclass.h"

class World : BaseClass
{
private:
    QVector<ItemWorld*> items;
    double speed;
    QString background;
public:
    World();
    ~World() override;
    void render() override;
    const QVector<ItemWorld*>& getItems() const;
};

#endif // WORLD_H
