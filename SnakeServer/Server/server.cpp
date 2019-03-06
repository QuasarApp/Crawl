#include "server.h"
#include <spserver.h>

Server::Server(QObject *ptr):
    QObject (ptr) {
    _serverDaemon = new  ServerProtocol::Server(this);
    _serverDaemon->run(DEFAULT_SERVER);
}

Server::~Server() {
}
