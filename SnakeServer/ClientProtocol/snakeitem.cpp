#include "snakeitem.h"

namespace ClientProtocol {

SnakeItem::SnakeItem() {

}

bool SnakeItem::isValid() {
    return BaseItem::isValid() && _spead > 0;
}

QDataStream &SnakeItem::operator <<(QDataStream &stream)  {
    BaseItem::operator<<(stream);
    stream >> _spead;

    return stream;
}

QDataStream &SnakeItem::operator >>(QDataStream &stream) const {

    BaseItem::operator>>(stream);
    stream << _spead;

    return stream;

}

}


