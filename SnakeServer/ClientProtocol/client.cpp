#include "client.h"
#include <QRegularExpression>
#include <QTcpSocket>
#include <QVariantMap>
#include <QDateTime>
#include <quasarapp.h>
#include "factorynetobjects.h"

namespace ClientProtocol {

bool Client::receiveData(QVariantMap map) {

    auto command = static_cast<NetworkClasses::Type>(map.value("command", Undefined).toInt());
    auto type = static_cast<Type>(map.value("type", 2).toInt());
    int  index = map.value("sig", -1).toInt();

    if (index < 0 || index > 255)
        return false;

#define idx static_cast<quint8>(index)

    auto expectedCommand = static_cast<NetworkClasses::Type>(_requestsMap[idx].value("expected", NetworkClasses::Undefined).toInt());

    if (!expectedCommand || (command != expectedCommand) || type != Responke) {
        QuasarAppUtils::Params::verboseLog("wrong sig of package");
        return false;
    }

    map["time"] = QDateTime::currentMSecsSinceEpoch();
    _requestsMap[idx] = map;

    if (expectedCommand != NetworkClasses::Undefined &&
            (command == expectedCommand) && type == Responke) {

        setOnline(static_cast<quint32>(map.value("token", "").toByteArray().size()) ==
                  NetworkClasses::getSizeType(NetworkClasses::SHA256));
    }

    emit sigIncommingData(map);

    return true;
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
        if (_downloadPackage.parse(res) && !receiveData(res)) {
            Q_UNUSED(res);
            // ban
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

bool Client::sendPackage(Package &pkg) {
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

    auto index = nextIndex();
    _requestsMap[index] = {{"expected", static_cast<const unsigned short>(pkg.hdr.command)}};
    pkg.hdr.sig = index;

    auto bytes = pkg.toBytes();
    bool sendet = bytes.size() == _destination->write(bytes);

    return sendet;
}

unsigned char Client::nextIndex() {
    return static_cast<unsigned char>((currentIndex++) % 256);
}

bool Client::ping() {

    Package pcg;

    QVariantMap map;
    if (!(FactoryNetObjects::build(NetworkClasses::Ping, map) && pcg.create(map, Request))) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;

    }

    return true;
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
    if (!FactoryNetObjects::build(NetworkClasses::Login, map)) {
        return false;
    };

    map["gmail"] = gmail;
    map["hashPass"] = pass;

    if (!pcg.create(map, Request)) {
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
    if (!FactoryNetObjects::build(NetworkClasses::UpdatePlayerData, map)) {
        return false;
    }

    map["token"] = _token;

    if (!pcg.create(map, Request)) {
        return false;
    };

    if (!sendPackage(pcg)) {
        return false;

    }

    return true;
}

bool Client::savaData(const QList<int>& gameData) {
    if (!isOnline()) {
        return false;
    }

    Package pcg;

    QVariantMap map;
    if (!FactoryNetObjects::build(NetworkClasses::Game, map)) {
        return false;
    }

    map["token"] = _token;
    map["time"] = FactoryNetObjects::buildArray(gameData);

    if (!pcg.create(map, Request)) {
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
    if (!FactoryNetObjects::build(NetworkClasses::GetItem, map)) {
        return false;
    }

    map["token"] = _token;
    map["id"] = id;

    if (!pcg.create(map, Request)) {
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
