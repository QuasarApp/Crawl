#include "snake.h"
#include "guiobject.h"

#include <QMap>
#include <QRectF>
#include <cmath>

Snake::Snake() {
}

const QVector<Head *> &Snake::getItems() const {
    return items;
}

void Snake::render() {
    for (int i = items.length() - 1; i >= 0; --i) {

        if(i == 0) {
            if(isClick){
                if(countClick & 1){
                    items[i]->setAngle(45);
                }else{
                    items[i]->setAngle(315);
                }
                isClick = false;
            }
        }else  {
            double _atan2 = atan2(items[i - 1]->rect().center().y() - items[i]->rect().center().y(),
                    items[i - 1]->rect().center().x() - items[i]->rect().center().x()) * 180;

            items[i]->setAngle(_atan2);
        }

        items[i]->render();
    }
}

double Snake::checDistance(int i) {

    auto result = (items[i]->rect().y() -
    items[i - 1]->rect().y()) / rataticonDistance;

    return result;

}

double Snake::getRataticonDistance() const {
    return rataticonDistance;
}

void Snake::setRataticonDistance(double value) {
    rataticonDistance = value;
}

void Snake::changeCountObjects(int count) {
    if (count > 0) {
        double margin = 60.0 / count;
        for ( int i = 0; i < count; ++i ) {
            auto obj = new Head(margin * (count - i),
                                50, 7, 7, this->speed);

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

QMap<int, GuiObject*> Snake::init(int size, double *speed) {

    QMap<int, GuiObject*> res;

    if (size <= 0) {
        return res;
    }

    this->speed = speed;

    changeCountObjects(size - items.size());

    for (auto i : items) {
        res[i->guiId()] = i;
    }
    return res;
}

bool Snake::isInited() const {
    return items.size();
}

void Snake::clearItems() {
    for (auto i : items) {
        delete i;
    }
    items.clear();
}

void Snake::resetPosotion() {
    double margin = 60.0 / items.size();

    for ( int i = 0; i < items.size(); ++i ) {
        items[i]->setX(margin * (items.size() - i));
        items[i]->setY(50);
        items[i]->setAngle(0);
    }
}

Snake::~Snake() {
    clearItems();
}

void Snake::clear() {
    clearItems();
}

void Snake::reverse() {
    if (isClick) {
        return;
    }
    isClick = true;
    countClick++;
}
