#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include "serverprotocol_global.h"

#include <QVariantMap>

#define DEFAULT_PORT 9200
#define DEFAULT_GAME_PORT 7777

namespace ServerProtocol {

enum Type: unsigned char {
    Responke = 0,
    Request = 1
};

enum Command: unsigned char {
    undefined = 0x00,
    ping = 0x01,
};

struct Header {
    unsigned char size: 4;
    unsigned char type: 1;
    unsigned char command: 3;

    Header();

    bool isValid() const;
};

struct Package {
    Header hdr;
    QByteArray data;
    bool isValid() const;
    QVariantMap parse() const;
    QByteArray toBytes() const;

};

}

#endif // SERVERPROTOCOL_H
