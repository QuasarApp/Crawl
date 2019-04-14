#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include "clientprotocol_global.h"

#include <QVariantMap>
#include <snakeutils.h>
#include "config.h"
#include "networkclasses.h"

namespace ClientProtocol {

enum Type: unsigned char {
    Undefined = 0x00,
    Responke = 0x01,
    Request = 0x02,
    Stream = 0x03,
};

//enum class Command: unsigned char {
//    Undefined = 0x00,
//    Ping = 0x01,
//    Item = 0x02,
//    Login = 0x03,
//    PlayerData = 0x04,
//    SaveData = 0x05

//};

unsigned int getSize(NetworkClasses::Type type, bool isMax = false);
bool isStaticObject(NetworkClasses::Type type, unsigned int &max, unsigned int &min);
bool isValidSize(NetworkClasses::Type type, unsigned int size);
bool isValidMap(const QVariantMap &map);

/**
 * @brief The Header struct 8 byte
 */
#pragma pack(push, 1)
struct CLIENTPROTOCOLSHARED_EXPORT Header {
    /**
     * @brief size - size of package data (not header)
     */
    unsigned int size: 32;
    /**
     * @brief type of package see Type
     */
    unsigned char type: 8;
    /**
     * @brief command of pacage see Command
     */
    unsigned short command: 16;

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
    bool parse(QVariantMap &res) const;

    /**
     * @brief create - fill package
     * @param data - data of filled
     * @return true if all done
     */
    bool create(const QVariantMap &data, Type type);

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
