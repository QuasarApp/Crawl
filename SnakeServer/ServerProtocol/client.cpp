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
               array.data(), sizeof(unsigned char));
        _downloadPackage.data.append(array.mid(1));
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
}
