#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include "clientprotocol_global.h"

#include <QVariantMap>
#include <snakeutils.h>
#include "config.h"
#include "networkclasses.h"

namespace ClientProtocol {

enum Type: unsigned char {
    Responke = 0,
    Request = 1
};

enum Command: unsigned char {
    Undefined = 0x00,
    Ping = 0x01,
    Item = 0x02,
    Login = 0x03,
    PlayerData = 0x04,
    ApplyData = 0x05

};

int getSize(NetworkClasses::Type type, bool isMax = true);
bool isStaticObject(NetworkClasses::Type type, int& max, int &min);
bool isValidSize(NetworkClasses::Type type, int size);


/**
 * @brief The Header struct 4 byte
 */
struct CLIENTPROTOCOLSHARED_EXPORT Header {
    /**
     * @brief size - size of package data (not header)
     */
    unsigned int size: 20;
    /**
     * @brief type of package see Type
     */
    unsigned char type: 1;
    /**
     * @brief command of pacage see Command
     */
    unsigned char command: 3;

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
    bool parse(QVariantMap &res);

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
