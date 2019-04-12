#include "server.h"
#include <spserver.h>

bool Server::saveConfiguration()
{

}

bool Server::loadConfiguration()
{

}

bool Server::resetDefaultConfiguration()
{

}

Server::Server(QObject *ptr):
    QObject (ptr) {
    _serverDaemon = new  ServerProtocol::Server(this);
    _serverDaemon->run(DEFAULT_SERVER);
}

Server::~Server() {
}
