#include "mainserver.h"
#include <spserver.h>
#include <cpserver.h>

bool MainServer::restartSrver(const QString &ip, unsigned short port) {
    if (_serverDaemon->isListening()) {
        _serverDaemon->stop();
    }

    if (!_serverDaemon->run(ip, port)) {
        return false;
    }

    return true;
}

void MainServer::handleRequest(QVariantMap obj, const QHostAddress &addres) {

}

void MainServer::handleTerminalRequest(QVariantMap obj) {

    auto command = static_cast<ServerProtocol::Command>(obj.value("command").toInt());
    QVariantMap res;

    if (command == ServerProtocol::Command::State) {
        res ["Work State"] = _serverDaemon->getWorkState();
        res ["Connections count"] = _serverDaemon->connectionState();
        auto banedList = _serverDaemon->baned();
        res ["Baned Addresses count"] = banedList.size();
        res ["Baned List"] = banedList;

    }

    _terminalPort->sendResponce(res, command);
    return;
}

MainServer::MainServer(QObject *ptr):
    QObject (ptr) {
    _serverDaemon = new  ClientProtocol::Server(this);
    _terminalPort = new  ServerProtocol::Server(this);

    connect(_serverDaemon, &ClientProtocol::Server::incomingReques,
            this, &MainServer::handleRequest);

    connect(_terminalPort, &ServerProtocol::Server::incomingRequest,
            this, &MainServer::handleTerminalRequest);

}

bool MainServer::run() {

    if (!_terminalPort->run(DEFAULT_SERVER)) {
        return false;
    }

    if (!restartSrver(DEFAULT_SNAKE_SERVER, DEFAULT_SNAKE_PORT)) {
        return false;
    }

    return true;

}

MainServer::~MainServer() {
}
