#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include "clientprotocol_global.h"

#include <QVariantMap>

#define DEFAULT_SNAKE_SERVER    "127.0.0.1"
#define LOCAL_SNAKE_SERVER    "127.0.0.1"

#define DEFAULT_SNAKE_PORT      7777

namespace ClientProtocol {

enum Class: unsigned char {
    SnakeData = 0
};

enum Type: unsigned char {
    Responke = 0,
    Request = 1
};

enum Command: unsigned char {
    Undefined = 0x00,
    Ping = 0x01,
    Item = 0x02,
    Login = 0x03,
    PlayerData = 0x04
};

/**
 * @brief The Header struct 1 byte
 */
struct Header {
    /**
     * @brief size - size of package data (not header)
     */
    unsigned short size: 10;
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
    bool parse(QVariantMap &res) const;

    /**
     * @brief create - fill package
     * @param data - data of filled
     * @return true if all done
     */
    bool create(const QVariantMap &data);

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
