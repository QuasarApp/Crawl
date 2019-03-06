#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include "serverprotocol_global.h"

#include <QVariantMap>

#define DEFAULT_SERVER "SnnakeServer"

namespace ServerProtocol {

enum Type: unsigned char {
    Responke = 0,
    Request = 1
};

enum Command: unsigned char {
    undefined = 0x00,
    ping = 0x01,
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

#endif // SERVERPROTOCOL_H
