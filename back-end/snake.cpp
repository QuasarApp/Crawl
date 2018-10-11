#include "snake.h"
#include "guiobject.h"

#include <QMap>
#include <QRectF>

Snake::Snake() :
    speed(SPEEDSNAKE) {
}

const QVector<Head *> &Snake::getItems() const {
    return items;
}

void Snake::render() {
    for (int i = items.length(); i >= 0; --i) {
        if(i == 0){
            if(isClick){
                if(countClick & 1){
                    items[i]->setAngle(45);
                }else{
                    items[i]->setAngle(315);
                }
            }
        }else{
            items[i]->setAngle(items[i-1]->angle());
        }
    }
}

QMap<int, GuiObject*> Snake::init(int size, double speed) {

    QMap<int, GuiObject*> res;

    if (size < 0 || speed <= 0) {
        return res;
    }

    this->speed = speed;

    if (!size) {
        size ++;
    }

    for ( int i = size; i >= 0; --i ) {
        auto obj = new Head(&this->speed);
        items.push_back(obj);
        res[obj->guiId()] = obj;
    }

    return res;
}

Snake::~Snake() {
    for (auto i : items) {
        delete i;
    }
    items.clear();

}

const QRectF& Snake::getRiger() const {
    return items.first()->getRect();
}
