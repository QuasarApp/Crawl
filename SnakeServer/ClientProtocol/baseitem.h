#ifndef BASEITEM_H
#define BASEITEM_H
#include "clientprotocol_global.h"
#include <QDataStream>

namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT BaseItem {
public:
    explicit BaseItem() = delete;

    static bool read(QDataStream &stream, QVariantMap &map);
    static bool write(QDataStream &stream, const QVariantMap &map);
};

}


#endif // BASEITEM_H
