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
                isClick = false;
            }
        }else{
            items[i]->setAngle(items[i-1]->angle());
        }
        items[i]->render();
    }
}

void Snake::changeCountObjects(int count) {
    if (count > 0) {
        double margin = 40.0 / count;
        for ( int i = 0; i < count; ++i ) {
            QRectF rect(margin * (count - i), 50, 10, 10);
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

void Snake::reverse() {
    if (isClick) {
        return;
    }
    isClick = true;
    countClick++;
}

const QRectF& Snake::getRiger() const {
    return items.first()->getRect();
}
