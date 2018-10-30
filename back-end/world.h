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
    double currentLong;
    int endLong;
    double spead;
    QString background;
    double speed;
    qint64 time;
    bool defiat = false;
    WorldRules oldRules;

    void clearItems();

    void changeCountObjects(const QString &name, int count);

public:
    World();
    QMap<int, GuiObject*> init(const WorldRules &rules);
    ~World() override;
    void render() override;
    bool move();
    bool isEnd();
    const QVector<ItemWorld*>& getItems() const;
    bool isDefiat() const;
};

#endif // WORLD_H
