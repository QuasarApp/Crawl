#include "snake.h"


Snake::Snake() :
    speed(SPEEDSNAKE){
}

const QVector<Head *> &Snake::getItems() const {
    return items;
}

void Snake::render() {
    for (auto i = items.rbegin(); i != items.rend(); ++i) {
        if(i==items.rend()-1){
            if(isClick){
                if(countClick & 1){
                    (*i)->setAngle(45);
                }else{
                    (*i)->setAngle(315);
                }
            }
        }else{

        }
        (*i)->render();
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
