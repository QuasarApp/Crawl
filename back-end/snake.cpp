#include "snake.h"

void Snake::setItems(const QVector<Head *> &value)
{
    items = value;
}

QVector<Head *> Snake::getItems() const
{
    return items;
}

void Snake::setSpeedHead(){
    for(int i = 0;i < getItems().size(); ++i){
        getItems().at(i)->setSpeed(&speed);
    }
}

Snake::Snake() :
    speed(SPEEDSNAKE)
{
    setSpeedHead();
}
