#include "server.h"
#include "quasarapp.h"
#include <QTcpSocket>

namespace ClientProtocol {

bool Server::parsePackage(const Package &pkg, QTcpSocket* sender) {
    if (!pkg.isValid()) {
        QuasarAppUtils::Params::verboseLog("incomming package is not valid!");
        return false;
    }

    if (!sender->isValid()) {
        QuasarAppUtils::Params::verboseLog("incomming package is not valid!");
        return false;
    }

    switch (pkg.hdr.command) {
    case ping: {

        if (pkg.hdr.type != Responke) {
            return false;
        }

        Package resp;
        resp.hdr.command = ping;

        auto bytes = resp.toBytes();

        if (bytes.size() != sender->write(bytes)) {
            QuasarAppUtils::Params::verboseLog("!responce not sendet!");
        }
        break;
    }

    default:{
        QuasarAppUtils::Params::verboseLog("!responce not sendet!");
        return false;
    }
    }

    return true;
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
               array.data(), sizeof(unsigned char));
        _downloadPackage.data.append(array.mid(1));
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
        connect(socket, &QTcpSocket::readyRead, this,  &Server::avelableBytes);
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

}
