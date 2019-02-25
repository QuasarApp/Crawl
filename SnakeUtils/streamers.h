#ifndef STEAMERS_H
#define STEAMERS_H

#include <QVariantMap>
#include "snakeutils.h"

class QDataStream;

class Streamers {

private:
    static SnakeUtils::Type baseRead(QDataStream &stream, QVariantMap &map);
    static SnakeUtils::Type baseWrite(QDataStream &stream, const QVariantMap &map);

public:

    static bool read(QDataStream &stream, QVariantMap &map);
    static bool write(QDataStream &stream, const QVariantMap &map);
    static bool isVaidSize(SnakeUtils::Type type);

    static bool isGeneralObject(SnakeUtils::Type);
    Streamers() = delete;
};

#endif // STEAMERS_H
