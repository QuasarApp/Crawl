#include "snake.h"

const QVector<Head *> &Snake::getItems() const {
    return _items;
}

Snake::Snake() :
    _speed(SPEEDSNAKE){
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
