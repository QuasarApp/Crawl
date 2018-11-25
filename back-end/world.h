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
    QVector<ItemWorld*> items;
    double currentLong = 0;
    int endLong;
    double spead = 0, d_spead = 0;
    QString background;
    qint64 time;
    bool defiat = false;
    WorldRules oldRules;

    void clearItems();

    void changeCountObjects(const QString &name, int count);

public:
    World();
    void clear();
    QMap<int, GuiObject*> init(const WorldRules &rules);
    ~World() override;
    void render() override;
    void resetPosition();
    bool move();
    bool isEnd();
    const QVector<ItemWorld*>& getItems() const;
    bool isDefiat() const;
    WorldRules currentRules() const;
    void reversClick();
    double getCurrentLong() const;
};

#endif // WORLD_H
