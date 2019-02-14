#include "baseitem.h"

#include <QVariantMap>

namespace ClientProtocol {

bool BaseItem::read(QDataStream &stream ,QVariantMap &map) {

    unsigned int id;

    stream >> id;
    map["id"] = id;

    return id;
}

bool BaseItem::write( QDataStream &stream, const QVariantMap &map) {
    unsigned int id = map.value("id", 0).toUInt();
    stream << id;

    return id;
}

}


