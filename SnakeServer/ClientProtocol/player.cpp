#include "player.h"

#include <QVariantList>
namespace ClientProtocol {

bool Player::read(QDataStream &stream, QVariantMap &map) {
    if (!BaseItem::read(stream, map)) {
        return false;
    }

    QString name;
    QString gmail;
    unsigned int maney;
    unsigned int record;
    QList<unsigned int> items;
    unsigned int currentSnake;

    stream >> name;
    stream >> gmail;
    stream >> maney;
    stream >> record;
    stream >> items;
    stream >> currentSnake;
    QVariantList varList;

    for (auto i : items) {
        varList.push_back(i);
    }

    map["name"] = name;
    map["gmail"] = gmail;
    map["maney"] = maney;
    map["record"] = record;
    map["items"] = varList;
    map["currentSnake"] = currentSnake;

    return stream.status() == QDataStream::Ok ||
           stream.status() == QDataStream::ReadPastEnd;

}

bool Player::write(QDataStream &stream, const QVariantMap &map) {
    if (!BaseItem::write(stream, map)) {
        return false;
    }

    stream << map.value("name").toString();
    stream << map.value("gmail").toString();
    stream << map.value("maney").toUInt();
    stream << map.value("record").toUInt();

    QList<unsigned int> items;
    auto varList = map.value("items").toList();
    for (auto &&i : varList) {
        items.push_back(i.toUInt());
    }
    stream << items;

    stream << map.value("currentSnake").toUInt();

    return stream.status() == QDataStream::Ok ||
           stream.status() == QDataStream::ReadPastEnd;
}

}
