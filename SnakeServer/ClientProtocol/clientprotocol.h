#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include "clientprotocol_global.h"

#include <QVariantMap>
#include <snakeutils.h>
#include "config.h"

namespace ClientProtocol {

class BaseNetworkObject;

enum class Type: quint8 {
    Undefined = 0x00,
    Responke = 0x01,
    Request = 0x02,
    Stream = 0x03,
};

enum class Command: quint8 {
    Undefined = 0x00,
    Ping = 0x01,
    BadRequest = 0x02,
    Login = 0x03,
    UpdatePlayerData = 0x04,
    GameData = 0x05,
    GetItem = 0x06,
    Player = 0x07,
    Snake = 0x08,
    Map = 0x08
};

bool isValidSize(quint8 type, unsigned int size);

bool initClientProtockol();

/**
 * @brief The Header struct 4 byte
 */
#pragma pack(push, 1)
struct CLIENTPROTOCOLSHARED_EXPORT Header {
    /**
     * @brief size - size of package data (not header)
     */
    unsigned short size: 16;
    /**
     * @brief type of package see Type
     */
    quint8 type: 2;
    /**
     * @brief command of pacage see Command
     */
    quint8 command: 6;

    /**
     * @brief sig
     * signed of package (package number)
     */
    unsigned char sig : 8;


    /**
     * @brief Header default constructor
     */
    Header();

    /**
     * @brief isValid
     * @return true if header is valid
     */
    bool isValid() const;


    /**
     * @brief reset - reset all data and set for header invalid status
     */
    void reset();
};
#pragma pack(pop)

/**
 * @brief The Package struct
 */
struct CLIENTPROTOCOLSHARED_EXPORT Package {
    /**
     * @brief hdr - header of package
     */
    Header hdr;
    /**
     * @brief data - source data of package
     */
    QByteArray data;

    Package();

    /**
     * @brief isValid
     * @return true if package is valid
     */
    bool isValid() const;

    /**
     * @brief parse
     * @return Qmap of package (default key if "value")
     */
    BaseNetworkObject * parse() const;

    /**
     * @brief create - fill package
     * @param data - data of filled
     * @return true if all done
     */
    bool create(const BaseNetworkObject *data, Type type);

    /**
     * @brief create
     * @param cmd command of package
     * @param type type
     * @return
     */
    bool create(Command cmd, Type type);

    /**
     * @brief toBytes
     * @return bytes array of packag
     */
    QByteArray toBytes() const;

    /**
     * @brief reset - reset all data and set for package invalid status
     */
    void reset();

};

}

#endif // CLIENTPROTOCOL_H
