#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include "rsakeyspool.h"


class QTcpSocket;
namespace ClientProtocol {

#define NOT_VALID_CARMA 0xFF
#define DEFAULT_KARMA   100
#define RESTORE_KARMA   20
#define BANED_KARMA     0

class Connectioninfo {

    QTcpSocket *sct = nullptr;
    int karma = DEFAULT_KARMA;
    RSAKeyPair RSAKey;

public:
    void disconnect();

    void ban();
    bool isBaned() const;
    void unBan();

    bool isValid() const;

    Connectioninfo(QTcpSocket * tcp = nullptr,
                   int kar = NOT_VALID_CARMA,
                   RSAKeyPair keys = RSAKeyPair());
    ~Connectioninfo();

    int getKarma() const;
    void setKarma(int value);
    RSAKeyPair getRSAKey() const;
    void setRSAKey(const RSAKeyPair &value);
    QTcpSocket *getSct() const;
    void setSct(QTcpSocket *value);
};
}
#endif // CONNECTIONINFO_H
