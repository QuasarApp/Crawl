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
    for (int i = items.length() - 1; i >= 0; --i) {
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

void Snake::changeCountObjects(int count) {
    if (count > 0) {

        for ( int i = 0; i < count; ++i ) {
            QRectF rect(0 + 10 * (count - i), 0, 10, 10);
            auto obj = new Head(rect, &this->speed);

            items.push_back(obj);
        }

    } else {
        for ( int i = count; i < 0; ++i ) {
            auto obj = items.first();
            items.removeFirst();
            delete obj;
        }
    }
}

QMap<int, GuiObject*> Snake::init(int size, double speed) {

    QMap<int, GuiObject*> res;

    if (size <= 0 || speed <= 0) {
        return res;
    }

    this->speed = speed;

    changeCountObjects(size -items.size());

    for (auto i : items) {
        res[i->guiId()] = i;
    }

    return res;
}

bool Snake::isInited() const {
    return items.size();
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
