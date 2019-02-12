#include "baseitem.h"

namespace ClientProtocol {
BaseItem::BaseItem() {

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

QDataStream &BaseItem::operator >>(QDataStream &stream) const{
    stream << _id;

    return stream;
}
}


