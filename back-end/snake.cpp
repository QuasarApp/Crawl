#include "snake.h"


Snake::Snake() :
    speed(SPEEDSNAKE){
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
            items[i]->setAngle(items[i-1]->getAngle());
        }
    }
}

bool Snake::init(int size, double speed) {

    if (size < 0 || speed <= 0) {
        return false;
    }

    this->speed = speed;

    for ( int i = size; i >= 0; --i ) {
        items.push_back( new Head(&this->speed));
    }

    return true;

}

Snake::~Snake() {
    for (auto i : items) {
        delete i;
    }
    items.clear();

}
