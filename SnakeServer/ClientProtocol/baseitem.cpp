#include "baseitem.h"

namespace ClientProtocol {
unsigned int BaseItem::id() const {
    return _id;
}

BaseItem::BaseItem(unsigned int id) {
    _id = id;
}

BaseItem::~BaseItem() {
}

bool BaseItem::isValid() {
    return _id > 0;
}

QDataStream& BaseItem::operator <<(QDataStream &stream)  {
    stream >> _id;

    return stream;
}

bool BaseItem::operator ==(const BaseItem & item) {
    return _id == item._id;
}

QDataStream &BaseItem::operator >>(QDataStream &stream) const{
    stream << _id;

    return stream;
}
}


