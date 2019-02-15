#include "client.h"
#include <QRegularExpression>
#include <QTcpSocket>
#include <QVariantMap>

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
        QVariantMap res;
        if (_downloadPackage.parse(res)) {
            emit sigIncommingData(res);
        }

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

bool Client::login(const QString &gmail, const QByteArray &pass) {
    if (!pass.size()) {
        return false;
    }

    if (!gmail.size()) {
        return false;
    }

    Package pcg;
    QVariantMap map;
    map["gmail"] = gmail;
    map["type"] = Request;
    map["hash"] = pass;
    if (!pcg.create(map)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;

    }

    return true;
}

bool Client::updateData(const QString &gmail, const QByteArray &pass) {
    return login(gmail, pass);
}

bool Client::getItem(int id, const QByteArray &pass) {
    if (!pass.size()) {
        return false;
    }

    if (!id) {
        return false;
    }

    Package pcg;
    QVariantMap map;
    map["id"] = id;
    map["hash"] = pass;
    if (!pcg.create(map)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;

    }

    return true;
}

}
