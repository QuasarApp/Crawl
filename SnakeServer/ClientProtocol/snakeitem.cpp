#include "snakeitem.h"

#include <QVariantMap>

namespace ClientProtocol {


bool SnakeItem::read(QDataStream &stream, QVariantMap &map) {

    if (!BaseItem::read(stream, map)) {
        return false;
    };

    unsigned char spead;
    QList<float> skillet;

    stream >> spead;
    stream >> skillet;
    QVariantList varList;

    for (auto i : skillet) {
        varList.push_back(i);
    }

    map["spead"] = spead;
    map["skillet"] = varList;

    return stream.status() == QDataStream::Ok ||
           stream.status() == QDataStream::ReadPastEnd;
}

bool SnakeItem::write(QDataStream &stream ,const QVariantMap &map) {

    if (!BaseItem::write(stream, map)) {
        return false;
    };

    stream << static_cast<quint8>(map.value("spead").toUInt());

    QList<float> skillet;
    auto varList = map.value("skillet").toList();
    for (auto &&i : varList) {
        skillet.push_back(i.toFloat());
    }

    stream << skillet;

    return stream.status() == QDataStream::Ok ||
           stream.status() == QDataStream::ReadPastEnd;
}

}


