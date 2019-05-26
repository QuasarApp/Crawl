#include "server.h"
#include "quasarapp.h"
#include <QTcpSocket>
#include <factorynetobjects.h>
#include "clientprotocol.h"

namespace ClientProtocol {

bool Server::parsePackage(const Package &pkg, QTcpSocket* sender) {
    if (!pkg.isValid()) {
        QuasarAppUtils::Params::verboseLog("incomming package is not valid!");
        changeKarma(qHash(sender->peerAddress()), CRITICAL_ERROOR);
        return false;
    }

    if (!sender->isValid()) {
        QuasarAppUtils::Params::verboseLog("incomming package is not valid!");
        changeKarma(qHash(sender->peerAddress()), LOGICK_ERROOR);
        return false;
    }

    switch (static_cast<Command>(pkg.hdr.command)) {
    case Command::Ping: {

        if (static_cast<Type>(pkg.hdr.type) != Type::Request) {
            return false;
        }

        Package pcg;

        if (!(pcg.create(Command::Ping, Type::Responke))) {
            return false;
        };

        pcg.hdr.sig = pkg.hdr.sig;

        if (!sendPackage(pcg, sender)) {
            QuasarAppUtils::Params::verboseLog("!responce not sendet!");
        }
        break;
    }

    default: {

        emit incomingReques(static_cast<Command>(pkg.hdr.command),
                            pkg.data, qHash(sender->peerAddress()));
    }
    }

    return true;
}

bool Server::sendPackage(Package &pkg, QTcpSocket * target) {
    if (!pkg.isValid()) {
        return false;
    }

    if (!target || !target->isValid()) {
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

void Server::ban(quint32 target) {
    _connections[target].karma = BANED_KARMA;
}

void Server::unBan(quint32 target) {
    _connections[target].karma = RESTORE_KARMA;
}

void Server::registerSocket(QTcpSocket *socket) {
    auto address = qHash(socket->peerAddress());

    _connections[address].karma = DEFAULT_KARMA;
    _connections[address].sct = socket;

    connect(socket, &QTcpSocket::readyRead, this,  &Server::avelableBytes);

}

bool Server::changeKarma(quint32 addresss, int diff) {
    auto objKarma = _connections.value(addresss).karma;

    if (objKarma >= NOT_VALID_CARMA) {
        return false;
    }

    if (objKarma <= BANED_KARMA) {
        return false;
    }

    _connections[addresss].karma += diff;
    return true;
}

bool Server::isBaned(const QTcpSocket * adr) const {
    return _connections.value(qHash(adr->peerAddress())).karma < 1;
}

void Server::saveKarma() const {

}

bool Server::loadKarma() {
    return false;
}

int Server::connectionsCount() const {
    int count = 0;
    for (auto i : _connections) {
        if (i.sct) {
            if (!i.sct->isValid()) {
                // log about warning
            }

            count++;
        }
    }
    return count;
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
        _connections.clear();
    }
}

void Server::badRequest(quint32 address) {
    auto client = _connections.value(address);

    if (!changeKarma(address, REQUEST_ERROR)) {
        return;
    }

    Package pcg;
    if (!(pcg.create(Command::BadRequest, Type::Responke))) {
        QuasarAppUtils::Params::verboseLog("Bad request detected, bud responce command nor received!",
                                           QuasarAppUtils::Error);
    };

    if (!sendPackage(pcg, client.sct)) {
        return;
    }
}

QString Server::getWorkState() const {
    if (isListening()) {
        if (hasPendingConnections())
            return "overload";
        else {
            return "Work";
        }
    }

    return "Not running";
}

QString Server::connectionState() const {
    return QString("%0 / %1").arg(connectionsCount()).arg(maxPendingConnections());
}

QStringList Server::baned() const {
    QStringList list = {};
    for (auto i = _connections.begin(); i != _connections.end(); ++i) {
        if (i.value().karma <= 0) {
            list.push_back(QHostAddress(i.key()).toString());
        }
    }

    return list;
}

Connectioninfo::Connectioninfo(QTcpSocket *tcp, int kar) {
    sct = tcp;
    karma = kar;
}

Connectioninfo::~Connectioninfo() {
    if (sct) {
        sct->deleteLater();
    }
}

}
