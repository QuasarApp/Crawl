#include "server.h"
#include <QLocalSocket>
#include <quasarapp.h>
#include <cstring>
#include <QFile>

#include "serverutils.h"
#include "serverprotocol.h"



namespace ServerProtocol {

void Server::parsePackage(const Package& pkg) {
    if (!pkg.isValid()) {
        return;
    }


    switch (pkg.hdr.command) {
    case ping: {

        if (pkg.hdr.type != Responke) {
            return;
        }

        Package resp;
        resp.hdr.command = ping;

        auto bytes = resp.toBytes();

        if (bytes.size() != _client->write(bytes)) {
            QuasarAppUtils::Params::verboseLog("!responce not sendet!");
        }
        break;
    }

    default: return;
    }
}

void Server::avelableBytes() {
    auto array = _client->readAll();

    if (_downloadPackage.hdr.isValid()) {
        _downloadPackage.data.append(array);

    } else {
        memcpy(&_downloadPackage.hdr,
               array.data(), sizeof(unsigned char));
        _downloadPackage.data.append(array.mid(1));
    }

    if (_downloadPackage.isValid()) {
        parsePackage(_downloadPackage);
        _downloadPackage.reset();
        return;
    }
}

void Server::incomingConnection(quintptr socketDescriptor) {
    _client->setSocketDescriptor(static_cast<qintptr>(socketDescriptor));

    if (!_client->isValid()) {
        QuasarAppUtils::Params::verboseLog("incomingConnection not valid!");
        return;
    }

    if (!_client->isOpen() && !_client->open()) {
        QuasarAppUtils::Params::verboseLog("incomingConnection not opened!");
        return;
    }
}

Server::Server(QObject *ptr):
    QLocalServer (ptr)
{
    _client = new QLocalSocket(this);

    connect(_client, &QLocalSocket::readyRead,
            this, &Server::avelableBytes);
}

Server::~Server() {
    close();
}

bool Server::run(const QString &name) {

    if (!listen(name) && !(QFile::remove("/tmp/" + name) && listen(name))) {
        QuasarAppUtils::Params::verboseLog("listing fail " + this->errorString());
        return false;
    }

    return true;
}
}
