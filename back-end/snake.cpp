#include "snake.h"


Snake::Snake() :
    _speed(SPEEDSNAKE){
}

const QVector<Head *> &Snake::getItems() const {
    return _items;
}

void Snake::render() {
// зздесь должна быть реализация рендера змейки
//    for (auto i : _items) {
//        i->render();
//    }
}

bool Snake::init(int size, double spead) {

    if (size < 0 || spead <= 0) {
        return false;
    }

    _speed = spead;

    for ( int i = size; i >= 0; --i ) {
        _items.push_back( new Head(&_speed));
    }

    return true;

}

Snake::~Snake() {
    for (auto i : _items) {
        delete i;
    }
    _items.clear();

}
