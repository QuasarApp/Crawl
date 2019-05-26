#include "mainserver.h"
#include "sqldbcache.h"
#include <spserver.h>
#include <cpserver.h>
#include <quasarapp.h>
#include <basenetworkobject.h>
#include <login.h>
#include <QCoreApplication>

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
        auto address = obj.value("address").toUInt();

        _serverDaemon->ban(address);
        auto banedList = _serverDaemon->baned();
        res ["Baned List"] = banedList;

        break;
    }

    case ServerProtocol::Unban: {
        auto address = obj.value("address").toUInt();
        _serverDaemon->unBan(address);
        auto banedList = _serverDaemon->baned();

        res ["Baned List"] = banedList;
        break;
    }

    case ServerProtocol::Restart: {
        auto address = obj.value("address").toString();
        auto port = static_cast<quint16>(obj.value("port").toInt());

        if (!restartSrver(address, port)) {
            QuasarAppUtils::Params::verboseLog("server restart fail!");
        }

        res ["Work State"] = _serverDaemon->getWorkState();
        res ["Address"] = QString("%0:%1").
                arg(_serverDaemon->serverAddress().toString()).
                arg(_serverDaemon->serverPort());


        break;
    }

    case ServerProtocol::Stop: {

        res ["Res"] = "Server stoped!";
        _terminalPort->sendResponce(res, command);
        _serverDaemon->stop();
        QCoreApplication::processEvents();
        QCoreApplication::quit();
        return;

    }

    default:
        QuasarAppUtils::Params::verboseLog("server get undefined command!");
        res ["Error"] = "Server get undefined command!";
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

bool MainServer::run(const QString &ip, unsigned short port, const QString& db,
                     const QString& terminalServer, bool terminalForce) {

    if (!_db->initDb((db.size())? db: DEFAULT_DB_PATH)) {
        QuasarAppUtils::Params::verboseLog("init db fail!", QuasarAppUtils::Error);
        return false;
    }

    if (!_terminalPort->run((terminalServer.isEmpty())? DEFAULT_SERVER : terminalServer,
                            terminalForce)) {
        QuasarAppUtils::Params::verboseLog("run termonal fail!", QuasarAppUtils::Error);
        return false;
    }

    if (!restartSrver(ip.isEmpty()? LOCAL_SNAKE_SERVER: ip,
                      port ? port : DEFAULT_SNAKE_PORT)) {
        QuasarAppUtils::Params::verboseLog("restart server fail", QuasarAppUtils::Error);
        return false;
    }

    return true;

}

MainServer::~MainServer() {
}
