#include "factorynetobjects.h"
#include "clientprotocol.h"

namespace ClientProtocol {

bool FactoryNetObjects::build(ClientProtocol::NetworkClasses::Type type, QVariantMap& item) {

    item.clear();

    item ["command"] = type;
    item ["id"] = -1;

    if (NetworkClasses::isCustomType(type)) {
        auto keys = networkObjects.value(type);

        for (auto i = keys.begin(); i != keys.end(); ++i) {
            if (NetworkClasses::isReal(i.value())) {
                item[i.key()] = 0.0;
            } else if (NetworkClasses::isInteger(i.value())) {
                item[i.key()] = 0;
            } else if (NetworkClasses::isString(i.value())) {
                item[i.key()] = "";
            } else if (NetworkClasses::isArray(i.value())) {

                QVariantMap array;
                if (!build(i.value(), array)) {
                    return false;
                }
                item[i.key()] = array.value("res");
            } else if (NetworkClasses::isCustomType(i.value())) {
                QVariantMap tempItem;
                if (!build(i.value(), tempItem)) {
                    return false;
                }
                item[i.key()] = tempItem;
            } else {
                return false;
            }
        }
    } else if (NetworkClasses::isArray(type)) {
        item["res"] = QVariantList();
    }

    return true;
}

bool FactoryNetObjects::fillRandomData(QVariantMap &item) {
    auto type = static_cast<NetworkClasses::Type>(
                item.value("command").toInt());

    if (NetworkClasses::isCustomType(type)) {
        auto keys = networkObjects.value(type);

        for (auto i = keys.begin(); i != keys.end(); ++i) {
            if (NetworkClasses::isReal(i.value())) {
                item[i.key()] = static_cast<double>((rand() % 1000) / 100.0);
            } else if (NetworkClasses::isInteger(i.value())) {
                item[i.key()] = static_cast<int>((rand() % 100));
            } else if (NetworkClasses::isString(i.value())) {
                item[i.key()] = QString("Random&0").arg(rand() % 1000);
            } else if (NetworkClasses::isArray(i.value())) {
                QVariantMap array;
                array["command"] = i.value();
                if (!fillRandomData(array)) {
                    return false;
                }
                item[i.key()] = array.value("res");
            } else if (NetworkClasses::isCustomType(i.value())) {
                QVariantMap tempItem;
                tempItem["command"] = i.value();
                tempItem["id"] = rand() % 10000;
                if (!fillRandomData(tempItem)) {
                    return false;
                }
                item[i.key()] = tempItem;
            } else {
                return false;
            }
        }
    } else if (NetworkClasses::isArray(type)) {

        int count = rand()% 10;
        auto typeArray = static_cast<NetworkClasses::Type>(type & ~NetworkClasses::Array);
        QVariantList res;

        if (NetworkClasses::isReal(typeArray)) {
            for (int i = 0; i < count ; ++i) {
                res.push_back(static_cast<double>((rand() % 1000) / 100.0));
            }
        } else if (NetworkClasses::isInteger(typeArray)) {
            for (int i = 0; i < count ; ++i) {
                res.push_back(static_cast<int>((rand() % 1000)));
            }
        } else if (NetworkClasses::isString(typeArray)) {
            for (int i = 0; i < count ; ++i) {
                res.push_back(QString("Random&0").arg(rand() % 1000));
            }
        } else if (NetworkClasses::isArray(typeArray)) {

            for (int i = 0; i < count ; ++i) {
                QVariantMap array;
                array["command"] = typeArray;
                if (!fillRandomData(array)) {
                    return false;
                }
                res.push_back(array.value("res"));
            }
        } else if (NetworkClasses::isCustomType(typeArray)) {
            QVariantMap resitem;
            resitem["command"] = typeArray;
            resitem["id"] = rand() % 10000;

            if (!fillRandomData(resitem)) {
                return false;
            }
            res.push_back(resitem);
        } else {
            return false;
        }

        item["res"] = res;
    }

    return true;
}

}
