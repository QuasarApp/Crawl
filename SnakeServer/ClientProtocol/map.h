#ifndef MAP_H
#define MAP_H
#include "baseitem.h"
#include "clientprotocol_global.h"

namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT Map : public BaseItem {
private:

public:
    Map() = delete;

    static bool read(QDataStream &stream, QVariantMap &map);
    static bool write(QDataStream &stream, const QVariantMap &map);
};
}

#endif // MAP_H
