#ifndef STEAMERS_H
#define STEAMERS_H

#include "clientprotocol_global.h"
#include <QVariantMap>
#include "snakeutils.h"
#include "networkclasses.h"

class QDataStream;
namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT Streamers {

private:
    static NetworkClasses::Type baseRead(QDataStream &stream, QVariantMap &map,
                                     const NetworkClasses::Type checkType);

    static NetworkClasses::Type baseWrite(QDataStream &stream, const QVariantMap &map);

public:

    static bool read(QDataStream &stream, QVariantMap &map,
                     const NetworkClasses::Type checkType = NetworkClasses::CustomType);
    static bool write(QDataStream &stream, const QVariantMap &map);
    static bool write(QByteArray &stream, const QVariantMap &map);


    static bool isGeneralObject(NetworkClasses::Type);
    Streamers() = delete;
};
}
#endif // STEAMERS_H
