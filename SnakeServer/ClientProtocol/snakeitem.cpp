#include "snakeitem.h"

namespace ClientProtocol {

SnakeItem::SnakeItem(unsigned int id):
    BaseItem (id) {

}

SnakeItem::~SnakeItem() {
}

bool SnakeItem::isValid() {
    return BaseItem::isValid() &&
            _spead > 0 &&
            _skillet.size() &&
            _skillet.size() < 15;
}

QDataStream &SnakeItem::operator <<(QDataStream &stream)  {
    BaseItem::operator<<(stream);
    stream >> _spead;
    stream >> _skillet;

    return stream;
}

QDataStream &SnakeItem::operator >>(QDataStream &stream) const {

    BaseItem::operator>>(stream);
    stream << _spead;
    stream << _skillet;

    return stream;
}

}


