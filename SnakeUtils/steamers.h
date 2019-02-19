#ifndef STEAMERS_H
#define STEAMERS_H

#include <QVariantMap>


class QDataStream;

class Steamers
{
private:
    static bool baseRead(QDataStream &stream, QVariantMap &map);
    static bool baseWrite(QDataStream &stream, const QVariantMap &map);

public:
    enum Type: unsigned char {
        Snake = 0x00,
        Player,
        Map,
        Game,
        GeneralObject = 0x80
    };

    static bool read(QDataStream &stream, QVariantMap &map, Type type);
    static bool write(QDataStream &stream, const QVariantMap &map, Type type);

    static bool isGeneralObject(Type);
    Steamers() = delete;
};

#endif // STEAMERS_H
