#include "client.h"
#include <QRegularExpression>
#include <QTcpSocket>
#include <QVariantMap>
#include <QDateTime>

namespace ClientProtocol {

void Client::receiveData(QVariantMap map) {

    auto command = static_cast<Command>(map.value("command", Undefined).toInt());
    auto type = static_cast<Type>(map.value("type", 2).toInt());
    int index = map.value("sig", -1).toInt();

    if (index < 0 || index > 255)
        return;

    map["time"] = QDateTime::currentMSecsSinceEpoch();
    _requestsMap[index] = map;

    if ((command == Login || command == PlayerData) && type == Responke) {

        _online = map.value("token", "").toByteArray().size() ==
                NetworkClasses::getSizeType(NetworkClasses::SHA256);
        emit onlineChanged(_online);
    }

}

void Client::setOnline(bool newStatus)
{
    if (newStatus != _online) {
        _online = newStatus;
        emit onlineChanged(_online);
    }
}

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
            receiveData(res);
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
    map["command"] = Command::Login;

    if (!pcg.create(map)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;

    }

    return true;
}

bool Client::updateData() {

    if (!isOnline()) {
        return false;
    }

    Package pcg;
    QVariantMap map;
    map["type"] = Request;
    map["token"] = _token;
    map["command"] = Command::PlayerData;

    if (!pcg.create(map)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;

    }

    return true;
}

bool Client::savaData(QVariantMap gameData) {
    if (!isOnline()) {
        return false;
    }

    Package pcg;
    gameData["type"] = Request;
    gameData["token"] = _token;
    gameData["command"] = Command::ApplyData;

    if (!pcg.create(gameData)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;
    }

    return true;
}

bool Client::getItem(int id) {

    if (!isOnline()) {
        return false;
    }

    if (!id) {
        return false;
    }

    Package pcg;
    QVariantMap map;
    map["id"] = id;
    map["type"] = Request;
    map["token"] = _token;
    map["command"] = Command::Item;

    if (!pcg.create(map)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;
    }

    return true;
}

bool Client::isOnline() const
{
    return _online;
}

}
