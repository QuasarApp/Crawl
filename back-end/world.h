#ifndef WORLD_H
#define WORLD_H

#define SPEEDWORLD 10

#include <QVector>
#include "itemworld.h"
#include "baseclass.h"
#include "utils.h"
#include "snake.h"

class World : public BaseClass
{
private:

    Snake snake;

private:
    QVector<ItemWorld*> items;
    double currentLong;
    int endLong;
    double spead;
    QString background;

    bool defiat = false;

    void clearItems();

public:
    World();
    QMap<int, GuiObject*> init(const WorldRules &rules);
    ~World() override;
    void render() override;
    bool move(double spead);
    bool isEnd();
    const QVector<ItemWorld*>& getItems() const;
    bool isDefiat() const;
};

#endif // WORLD_H
