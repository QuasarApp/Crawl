#include "steamers.h"

#include <QDataStream>
#include "networkobjects.h"
#include <QMap>

bool Steamers::baseRead(QDataStream &stream, QVariantMap &map) {
    unsigned int id;

    stream >> id;
    map["id"] = id;

    return id;
}

bool Steamers::baseWrite(QDataStream &stream, const QVariantMap &map) {
    unsigned int id = map.value("id", 0).toUInt();
    stream << id;

    return id;
}

unsigned int Steamers::getMaxSize(SnakeUtils::Type type) {
    auto size = SnakeUtils::getSizeType(type);
    if (size) {
        return size;
    }
    auto listPropertyes = networkObjects.value(type);
    size = 0;
    for (auto &&i : listPropertyes) {

        if (SnakeUtils::isArray(i)) {
            SnakeUtils::Type arrayType = static_cast<SnakeUtils::Type>(type & ~SnakeUtils::Array);

            auto sizeItem = SnakeUtils::getSizeType(arrayType);

        }

        size += getMaxSize(i);
    }

    return size;
}

int Steamers::getMinSize(Steamers::Type type) {

}

void Steamers::writeArray(QDataStream &stream, const QVariantList &map) {
    QList<unsigned int> items;
    auto varList = map.value("items").toList();
    for (auto &&i : varList) {
        items.push_back(i.toUInt());
    }
}

void Steamers::readArray(QDataStream &stream, QVariantList &map)
{

}

bool Steamers::read(QDataStream &stream, QVariantMap &map, SnakeUtils::Type type) {
    if (!baseRead(stream, map)) {
        return false;
    }

    auto parseRules = networkObjects.value(type);

    for (auto iter = parseRules.begin(); iter != parseRules.end(); ++iter) {

        auto property = iter.key();
        auto typeItem = iter.value();

        if (SnakeUtils::isNumber(typeItem)) {

            auto size = SnakeUtils::getSizeType(typeItem);

            if (size < 0)
                return false;

            char *data = new char[static_cast<unsigned int>(size)];

            if (size != stream.readRawData(data, size)) {
                return false;
            }

            map.insert(property, QVariant::fromValue(data));

        }
        else if (SnakeUtils::isString(type)) {
            QStringList val;
            stream >> val;
            map.insert(property, val);

        }
        else if (SnakeUtils::isArray(type)) {

            if (type & SnakeUtils::String) {
                QStringList list;
                stream >> list;
                map.insert(property, list);

            } else {
                SnakeUtils::Type arrayType = static_cast<SnakeUtils::Type>(type & ~SnakeUtils::Array);
                QByteArray array;
                stream >> array;

                QVariantList varList;

                auto size = SnakeUtils::getSizeType(arrayType);
                for (int i = 0; i < array.size(); i+= size) {
                    varList.push_back(QVariant::fromValue(array.mid(i, size)));
                }

                break;
            }
        }
    }

    return true;
}

bool Steamers::write(QDataStream &stream, const QVariantMap &map, SnakeUtils::Type type) {

    if (!baseWrite(stream, map)) {
        return false;
    }

    auto parseRules = networkObjects.value(type);

    for (auto iter = parseRules.begin(); iter != parseRules.end(); ++iter) {
        auto property = iter.key();
        auto typeItem = iter.value();
        auto value = map.value(property);

        if (SnakeUtils::isNumber(typeItem)) {

            auto val = value.toByteArray();
            auto size = SnakeUtils::getSizeType(typeItem);

            if (size != stream.writeRawData(val.data(), size)) {
                return false;
            }
        }
        else if (SnakeUtils::isString(type)) {
            stream << value.toString();
        }
        else if (SnakeUtils::isArray(type)) {
            if (type & SnakeUtils::String) {
                stream << value.toStringList();
            } else {
                SnakeUtils::Type arrayType = static_cast<SnakeUtils::Type>(type & ~SnakeUtils::Array);

                QByteArray array;
                auto varList = value.toList();
                for (auto &&i : varList) {
                    auto temp = i.toByteArray();

                    if (temp.size() != SnakeUtils::getSizeType(arrayType)) {
                        return false;
                    }

                    array.push_back(temp);
                }
                stream << array;
                break;
            }
        }
    }

    return true;
}

bool Steamers::isVaidSize(Type type) {
    return
}

bool Steamers::isGeneralObject(Steamers::Type t) {
    return t & Steamers::GeneralObject;
}
