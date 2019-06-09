#include "connectioninfo.h"
#include <QTcpSocket>

namespace ClientProtocol {


int Connectioninfo::getKarma() const {
    return karma;
}

void Connectioninfo::setKarma(int value) {
    karma = value;
}

RSAKeyPair Connectioninfo::getRSAKey() const {
    return RSAKey;
}

void Connectioninfo::setRSAKey(const RSAKeyPair &value) {
    RSAKey = value;
}

QTcpSocket *Connectioninfo::getSct() const {
    return sct;
}

void Connectioninfo::setSct(QTcpSocket *value) {
    sct = value;
}

void Connectioninfo::disconnect() {
    if (sct) {
        sct->close();
        delete sct;
        sct = nullptr;
    }
}

void Connectioninfo::ban() {
    karma = BANED_KARMA;
    disconnect();
}

bool Connectioninfo::isBaned() const {
    return karma < 1;
}

void Connectioninfo::unBan() {
    karma = RESTORE_KARMA;
}

bool Connectioninfo::isValid() const {
    return sct && !RSAKey.pub.isEmpty() && !RSAKey.priv.isEmpty();
}

Connectioninfo::Connectioninfo(QTcpSocket *tcp, int kar, RSAKeyPair keys) {
    sct = tcp;
    karma = kar;
    RSAKey = keys;
}

Connectioninfo::~Connectioninfo() {
    if (sct) {
        sct->deleteLater();
    }
}
}
