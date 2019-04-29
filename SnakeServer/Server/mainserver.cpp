#include "mainserver.h"
#include <spserver.h>
#include <cpserver.h>
#include <quasarapp.h>
#include <basenetworkobject.h>

bool MainServer::restartSrver(const QString &ip, unsigned short port) {
    if (_serverDaemon->isListening()) {
        _serverDaemon->stop();
    }

    if (!_serverDaemon->run(ip, port)) {
        return false;
    }

    return true;
}

void MainServer::handleRequest(ClientProtocol::BaseNetworkObject *obj,
                               const quint32 &addres) {

    Q_UNUSED(addres);

    auto command = static_cast<ClientProtocol::Command>
            (obj->getClass());

    switch (command) {
    case ClientProtocol::Command::Login: {
        break;
    }

    case ClientProtocol::Command::GameData: {
        break;
    }

    case ClientProtocol::Command::UpdatePlayerData: {
        break;
    }

    case ClientProtocol::Command::GetItem: {
        break;
    }

    default:
        _serverDaemon->badRequest(addres);
        break;
    }
}

void MainServer::handleTerminalRequest(QVariantMap obj) {

    auto command = static_cast<ServerProtocol::Command>(obj.value("command").toInt());
    QVariantMap res;

    switch (command) {
    case ServerProtocol::State: {
        res ["Work State"] = _serverDaemon->getWorkState();
        res ["Connections count"] = _serverDaemon->connectionState();

        auto banedList = _serverDaemon->baned();
        res ["Baned Addresses count"] = banedList.size();
        res ["Baned List"] = banedList;

        break;
    }
    case ServerProtocol::Ban: {
        auto address = static_cast<quint32>(obj.value("address").toInt());

        _serverDaemon->ban(address);
        break;
    }

    case ServerProtocol::Unban: {
        auto address = static_cast<quint32>(obj.value("address").toInt());

        _serverDaemon->unBan(address);
        break;
    }

    case ServerProtocol::Restart: {
        auto address = obj.value("address").toString();
        auto port = static_cast<quint16>(obj.value("address").toInt());

        if (!restartSrver(address, port)) {
            QuasarAppUtils::Params::verboseLog("server restart fail!");
        }

        break;
    }

    default:
        QuasarAppUtils::Params::verboseLog("server get undefined command!");
        break;
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
