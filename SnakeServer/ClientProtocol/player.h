#ifndef PLAYER_H
#define PLAYER_H
#include "clientprotocol_global.h"
#include "baseitem.h"
#include <QDataStream>
#include <QList>

#define MIN_SIZE_PLAYER 21
#define MAX_SIZE_PLAYER 128

namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT Player : public BaseItem {
private:

public:
    Player() = delete;

    static bool read(QDataStream &stream, QVariantMap &map);
    static bool write(QDataStream &stream, const QVariantMap &map);
};
}


#endif // PLAYER_H
