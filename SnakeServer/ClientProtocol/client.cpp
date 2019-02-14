#include "client.h"
#include <QTcpSocket>

namespace ClientProtocol {

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

    _destination = new QTcpSocket(this);

    _destination->connectToHost(DEFAULT_SNAKE_SERVER, DEFAULT_SNAKE_PORT);

    connect(_destination, &QTcpSocket::readyRead,
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

Player *Client::login(const QString &gmail, const QByteArray &pass, QString &error) {

}

bool Client::updateData(Player *) {

}

BaseItem *Client::getItem(int id) {

}

}
