#include "streamers.h"

#include <QDataStream>
#include "networkobjects.h"
#include <QMap>
#include <QVariant>
#include <QVariantMap>

SnakeUtils::Type Streamers::baseRead(QDataStream &stream, QVariantMap &map,
                                     const SnakeUtils::Type checkType) {
    unsigned int id;
    unsigned short _class;

    stream >> _class;
    stream >> id;
    map["id"] = id;
    map["class"] = _class;

    if (id) {
        return SnakeUtils::Undefined;
    }

    return static_cast<SnakeUtils::Type>(_class & checkType);
}

SnakeUtils::Type Streamers::baseWrite(QDataStream &stream, const QVariantMap &map) {
    unsigned int id = map.value("id", 0).toUInt();
    unsigned short _class = static_cast<unsigned short>(map.value("class").toUInt());

    if (id) {
        return SnakeUtils::Undefined;
    }

    stream << _class;
    stream << id;

    return static_cast<SnakeUtils::Type>(_class & SnakeUtils::CustomType);
}

bool Streamers::read(QDataStream &stream, QVariantMap &map, const SnakeUtils::Type checkType) {
    auto type = baseRead(stream, map, checkType);
    if (!type) {
        return false;
    }

    auto parseRules = networkObjects.value(type);

    for (auto iter = parseRules.begin(); iter != parseRules.end(); ++iter) {

        auto property = iter.key();
        auto typeItem = iter.value();

        if (SnakeUtils::isNumber(typeItem)) {

            int size = static_cast<int> (SnakeUtils::getSizeType(typeItem));

            if (!size)
                return false;

            char *data = new char[static_cast<unsigned int>(size)];
            if (size != stream.readRawData(data, size)) {
                return false;
            }

            map.insert(property, QVariant::fromValue(QByteArray(data, size)));

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

bool Streamers::write(QDataStream &stream, const QVariantMap &map) {

    auto type = baseWrite(stream, map);
    if (!type) {
        return false;
    }

    auto parseRules = networkObjects.value(type);

    for (auto iter = parseRules.begin(); iter != parseRules.end(); ++iter) {
        auto property = iter.key();
        auto typeItem = iter.value();
        auto value = map.value(property);

        if (SnakeUtils::isNumber(typeItem)) {

            auto val = value.toByteArray();
            auto size = static_cast<int>(SnakeUtils::getSizeType(typeItem));

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
