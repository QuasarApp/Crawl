#include "server.h"
#include "quasarapp.h"
#include <QTcpSocket>
#include <factorynetobjects.h>

namespace ClientProtocol {

bool Server::parsePackage(const Package &pkg, QTcpSocket* sender) {
    if (!pkg.isValid()) {
        QuasarAppUtils::Params::verboseLog("incomming package is not valid!");
        changeKarma(sender->peerAddress(), CRITICAL_ERROOR);
        return false;
    }

    if (!sender->isValid()) {
        QuasarAppUtils::Params::verboseLog("incomming package is not valid!");
        changeKarma(sender->peerAddress(), LOGICK_ERROOR);
        return false;
    }

    switch (pkg.hdr.command) {
    case NetworkClasses::Ping: {

        if (pkg.hdr.type != Request) {
            return false;
        }

        Package pcg;

        auto map = FactoryNetObjects::build(NetworkClasses::Ping);
        if (!pcg.create(map, Responke)) {
            return false;
        };

        if (!sendPackage(pcg, sender)) {
            QuasarAppUtils::Params::verboseLog("!responce not sendet!");
        }
        break;
    }

    default: {
        QVariantMap data;
        pkg.parse(data);
        emit incomingReques(data, sender->peerAddress());
    }
    }

    return true;
}

bool Server::sendPackage(Package &pkg, QTcpSocket * target) {
    if (!pkg.isValid()) {
        return false;
    }

    if (!target->isValid()) {
        qCritical() << "destination server not valid!";
        return false;
    }

    if (!target->waitForConnected()) {
        qCritical() << "no connected to server! " << target->errorString();
        return false;
    }

    auto bytes = pkg.toBytes();
    bool sendet = bytes.size() == target->write(bytes);

    return sendet;
}

void Server::ban(const QHostAddress& target) {
    _karma.insert(target, BANED_KARMA);
}

void Server::unBan(const QHostAddress& target) {
    _karma.insert(target, RESTORE_KARMA);
}

void Server::registerSocket(const QTcpSocket *socket) {
    if (!_karma.contains(socket->peerAddress())) {
        _karma.insert(socket->peerAddress(), DEFAULT_KARMA);
        connect(socket, &QTcpSocket::readyRead, this,  &Server::avelableBytes);
    }
}

bool Server::changeKarma(const QHostAddress &addresss, int diff) {
    int objKarma = _karma.value(addresss, NOT_VALID_CARMA);

    if (objKarma >= NOT_VALID_CARMA) {
        return false;
    }

    if (objKarma <= BANED_KARMA) {
        return false;
    }

    _karma.insert(addresss, objKarma + diff);
    return true;
}

bool Server::isBaned(const QTcpSocket * adr) const {
    return _karma.value(adr->peerAddress(), NOT_VALID_CARMA) < 1;
}

void Server::saveKarma() const {

}

bool Server::loadKarma() {
    return false;
}

void Server::avelableBytes() {
    auto client = dynamic_cast<QTcpSocket*>(sender());

    if (!client) {
        return;
    }

    auto array = client->readAll();

    if (_downloadPackage.hdr.isValid()) {
        _downloadPackage.data.append(array);

    } else {
        memcpy(&_downloadPackage.hdr,
               array.data(), sizeof(Header));
        _downloadPackage.data.append(array.mid(sizeof(Header)));
    }

    if (_downloadPackage.isValid()) {
        parsePackage(_downloadPackage, client);
        _downloadPackage.reset();
        return;
    }
}

void Server::handleIncommingConnection() {
    while (hasPendingConnections()) {
        auto socket = nextPendingConnection();

        if (isBaned(socket)) {
            socket->abort();
            break;
        }

        registerSocket(socket);
    }
}

Server::Server(QObject *ptr) :
    QTcpServer (ptr) {

    connect(this, &Server::newConnection, this, &Server::handleIncommingConnection);
}

Server::~Server() {

}

bool Server::run(const QString &ip, unsigned short port) {
    if (!listen(QHostAddress(ip), port) ) {
        QuasarAppUtils::Params::verboseLog("listing fail " + this->errorString());
        return false;
    }

    return true;
}

void Server::stop(bool reset) {
    close();

    if (reset) {
        for (auto socket: _connections) {
            socket->deleteLater();
        }
        _connections.clear();
    }
}

QString Server::getWorkState() const {
    if (isListening()) {
        if (hasPendingConnections())
            return "Work";
        else {
            return "overload";
        }
    }

    return "Not running";
}

QString Server::connectionState() const {
    return QString("%0 / %1").arg(_connections.size()).arg(maxPendingConnections());
}

QStringList Server::baned() const {
    QStringList list = {};
    for (auto i = _karma.begin() ; i != _karma.end(); i++) {
        if (i.value() <= 0) {
            list.push_back(i.key().toString());
        }
    }

    return list;
}

}
