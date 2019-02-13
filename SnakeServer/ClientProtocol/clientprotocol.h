#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include "clientprotocol_global.h"

#include <QVariantMap>

#define DEFAULT_SNAKE_SERVER    "127.0.0.1"
#define LOCAL_SNAKE_SERVER    "127.0.0.1"

#define DEFAULT_SNAKE_PORT      7777

namespace ClientProtocol {
enum Type: unsigned char {
    Responke = 0,
    Request = 1
};

enum Command: unsigned char {
    undefined = 0x00,
    ping = 0x01,
    item = 0x02,
    login = 0x04,
    playerData = 0x08
};

/**
 * @brief The Header struct 1 byte
 */
struct Header {
    /**
     * @brief size - size of package data (not header)
     */
    unsigned char size: 4;
    /**
     * @brief type of package see Type
     */
    unsigned char type: 1;
    /**
     * @brief command of pacage see Command
     */
    unsigned char command: 3;

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

/**
 * @brief The Package struct
 */
struct Package {
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
    QVariantMap parse() const;

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
