#include "mainserver.h"
#include "sqldbcache.h"
#include <spserver.h>
#include <cpserver.h>
#include <quasarapp.h>
#include <basenetworkobject.h>
#include <login.h>

bool MainServer::restartSrver(const QString &ip, unsigned short port) {
    if (_serverDaemon->isListening()) {
        _serverDaemon->stop();
    }

    if (!_serverDaemon->run(ip, port)) {
        return false;
    }

    return true;
}

void MainServer::handleRequest(ClientProtocol::Command cmd,
                               const QByteArray& data,
                               const quint32 &addres) {

    Q_UNUSED(addres);


    switch (cmd) {
    case ClientProtocol::Command::Login: {

        ClientProtocol::Login loginData;
        loginData.fromBytes(data);


        if (!loginData.isValid()) {
            _serverDaemon->badRequest(addres);
            return ;
        }

// TODO

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

    _db = new SqlDBCache();

    connect(_serverDaemon, &ClientProtocol::Server::incomingReques,
            this, &MainServer::handleRequest);

    connect(_terminalPort, &ServerProtocol::Server::incomingRequest,
            this, &MainServer::handleTerminalRequest);

}

bool MainServer::run(const QString &ip, unsigned short port, const QString& db) {

    if (!_db->initDb((db.size())? db: DEFAULT_DB_PATH)) {
        QuasarAppUtils::Params::verboseLog("init db fail!", QuasarAppUtils::Error);
        return false;
    }

    if (!_terminalPort->run(DEFAULT_SERVER)) {
        QuasarAppUtils::Params::verboseLog("run termonal fail!", QuasarAppUtils::Error);
        return false;
    }

    if (!restartSrver(ip.isEmpty()? DEFAULT_SNAKE_SERVER: ip,
                      port ? port : DEFAULT_SNAKE_PORT)) {
        QuasarAppUtils::Params::verboseLog("restart server fail", QuasarAppUtils::Error);
        return false;
    }

    return true;

}

MainServer::~MainServer() {
}
