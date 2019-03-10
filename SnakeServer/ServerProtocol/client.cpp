#include "client.h"
#include "serverprotocol.h"

#include <QLocalSocket>
#include <quasarapp.h>
#include <cstring>

namespace ServerProtocol {

void Client::incommingData() {
    auto array = _destination->readAll();

    if (_downloadPackage.hdr.isValid()) {
        _downloadPackage.data.append(array);

    } else {
        memcpy(&_downloadPackage.hdr,
               array.data(), sizeof(Header));
        _downloadPackage.data.append(array.mid(sizeof(Header)));
    }

    if (_downloadPackage.isValid()) {
        emit sigIncommingData(_downloadPackage.parse());
        _downloadPackage.reset();
        return;
    }
}

Client::Client(QObject *ptr):
    QObject (ptr) {

    _destination = new QLocalSocket(this);

    _destination->connectToServer(DEFAULT_SERVER);

    connect(_destination, &QLocalSocket::readyRead,
            this, &Client::incommingData);

}

bool Client::sendPackage(const Package &pkg) {
    if (!pkg.isValid()) {
        return false;
    }

    if (!_destination->isValid()) {
        qCritical() << "destination server not valid!";
        return false;
    }

    if (!_destination->waitForConnected()) {
        qCritical() << "no connected to server! " << _destination->errorString();
        return false;
    }

    auto bytes = pkg.toBytes();

    return bytes.size() == _destination->write(bytes);
}

bool Client::ping() {
    ServerProtocol::Package pkg;
    pkg.hdr.command = ServerProtocol::Ping;
    pkg.hdr.type = ServerProtocol::Request;

    return sendPackage(pkg);
}

bool Client::getState() {

    ServerProtocol::Package pkg;
    pkg.hdr.command = ServerProtocol::State;
    pkg.hdr.type = ServerProtocol::Request;

    return sendPackage(pkg);
}

bool Client::ban(const QHostAddress &address) {

    ServerProtocol::Package pkg;
    pkg.hdr.command = ServerProtocol::Ban;
    pkg.hdr.type = ServerProtocol::Request;

    QVariantMap map;
    map["address"] = qHash(address);

    pkg.fromMap(map);

    return sendPackage(pkg);
}

bool Client::unBan(const QHostAddress &address) {

    ServerProtocol::Package pkg;
    pkg.hdr.command = ServerProtocol::Unban;
    pkg.hdr.type = ServerProtocol::Request;

    QVariantMap map;
    map["address"] = qHash(address);

    pkg.fromMap(map);

    return sendPackage(pkg);
}

bool Client::restart(const QString &address, unsigned short port) {

    ServerProtocol::Package pkg;
    pkg.hdr.command = ServerProtocol::Restart;
    pkg.hdr.type = ServerProtocol::Request;

    QVariantMap map;
    map["address"] = address;
    map["port"] = port;
    pkg.fromMap(map);

    return sendPackage(pkg);
}
}
