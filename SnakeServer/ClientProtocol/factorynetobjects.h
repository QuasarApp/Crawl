#ifndef FACTORYNETOBJECTS_H
#define FACTORYNETOBJECTS_H
#include "clientprotocol_global.h"
#include "networkobjects.h"

namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT FactoryNetObjects {
public:
    FactoryNetObjects() = delete;

    static QVariantMap build(NetworkClasses::Type type);

    template <typename T>
    static QVariantList buildArray(const T& array) {

        QVariantList res;
        for (auto &&i : array) {
            res.push_back(i);
        }

        return res;
    }

};
}


#endif // FACTORYNETOBJECTS_H
