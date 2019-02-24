#ifndef STEAMERS_H
#define STEAMERS_H

#include <QVariantMap>
#include "snakeutils.h"

class QDataStream;

class Steamers
{
public:


private:


    static bool baseRead(QDataStream &stream, QVariantMap &map);
    static bool baseWrite(QDataStream &stream, const QVariantMap &map);

    static unsigned int getMaxSize(SnakeUtils::Type type);
    static int getMinSize(SnakeUtils::Type type);

    static void writeArray(QDataStream &stream, const QVariantList &map);
    static void readArray(QDataStream &stream,  QVariantList &map);

public:

    static bool read(QDataStream &stream, QVariantMap &map, SnakeUtils::Type type);
    static bool write(QDataStream &stream, const QVariantMap &map, SnakeUtils::Type type);
    static bool isVaidSize(SnakeUtils::Type type);

    static bool isGeneralObject(SnakeUtils::Type);
    Steamers() = delete;
};

#endif // STEAMERS_H
