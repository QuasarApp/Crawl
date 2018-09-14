#ifndef SNAKE_H
#define SNAKE_H

#define SPEEDSNAKE 10

#include <QVector>
#include "head.h"
#include "baseclass.h"

class Snake : public BaseClass
{
private:
    QVector<Head*> items;
    double speed;
    bool isClick;
    int countClick;
public:
    Snake();
    ~Snake() override;
    void render() override;
    bool init(int size, double speed);
    const QVector<Head*>& getItems() const;
    void setSpeedHead (void);
};

#endif // SNAKE_H
