#include "streamers.h"

#include <QDataStream>
#include "networkobjects.h"
#include <QMap>
#include <QVariant>
#include <QVariantMap>

namespace ClientProtocol {


NetworkClasses::Type Streamers::baseRead(QDataStream &stream, QVariantMap &map,
                                     const NetworkClasses::Type checkType) {
    unsigned int id;
    unsigned short _class;

    stream >> _class;
    stream >> id;
    map["id"] = id;
    map["class"] = _class;

    if (id) {
        return NetworkClasses::Undefined;
    }

    return static_cast<NetworkClasses::Type>(_class & checkType);
}

NetworkClasses::Type Streamers::baseWrite(QDataStream &stream, const QVariantMap &map) {
    unsigned int id = map.value("id", 0).toUInt();
    unsigned short _class = static_cast<unsigned short>(map.value("class").toUInt());

    if (id) {
        return NetworkClasses::Undefined;
    }

    stream << _class;
    stream << id;

    return static_cast<NetworkClasses::Type>(_class & NetworkClasses::CustomType);
}

bool Streamers::read(QDataStream &stream, QVariantMap &map, const NetworkClasses::Type checkType) {
    auto type = baseRead(stream, map, checkType);
    if (!type) {
        return false;
    }

    auto parseRules = networkObjects.value(type);

    for (auto iter = parseRules.begin(); iter != parseRules.end(); ++iter) {

        auto property = iter.key();
        auto typeItem = iter.value();

        if (NetworkClasses::isNumber(typeItem)) {

            int size = static_cast<int> (NetworkClasses::getSizeType(typeItem));

            if (!size)
                return false;

            char *data = new char[static_cast<unsigned int>(size)];
            if (size != stream.readRawData(data, size)) {
                return false;
            }

            map.insert(property, QVariant::fromValue(QByteArray(data, size)));

        }
        else if (NetworkClasses::isString(type)) {
            QStringList val;
            stream >> val;
            map.insert(property, val);

        }
        else if (NetworkClasses::isArray(type)) {

            if (type & NetworkClasses::String) {
                QStringList list;
                stream >> list;
                map.insert(property, list);

            } else {
                NetworkClasses::Type arrayType = static_cast<NetworkClasses::Type>(type & ~NetworkClasses::Array);
                QByteArray array;
                stream >> array;

                QVariantList varList;

                auto size = NetworkClasses::getSizeType(arrayType);
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

        if (NetworkClasses::isNumber(typeItem)) {

            auto val = value.toByteArray();
            auto size = static_cast<int>(NetworkClasses::getSizeType(typeItem));

            if (size != stream.writeRawData(val.data(), size)) {
                return false;
            }
        }
        else if (NetworkClasses::isString(type)) {
            stream << value.toString();
        }
        else if (NetworkClasses::isArray(type)) {
            if (type & NetworkClasses::String) {
                stream << value.toStringList();
            } else {
                NetworkClasses::Type arrayType = static_cast<NetworkClasses::Type>(type & ~NetworkClasses::Array);

                QByteArray array;
                auto varList = value.toList();
                for (auto &&i : varList) {
                    auto temp = i.toByteArray();

                    if (temp.size() != NetworkClasses::getSizeType(arrayType)) {
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
}
