#ifndef SERVER_H
#define SERVER_H
#include <serverprotocol.h>
#include "server_global.h"
#include <QHostAddress>
#include <clientprotocol.h>

namespace ServerProtocol {
    class Server;
}

namespace ClientProtocol {
    class Server;
    class BaseNetworkObject;
}

class SqlDBCache;

class SERVERSHARED_EXPORT MainServer: public QObject
{
    Q_OBJECT
private:
    ServerProtocol::Server *_terminalPort = nullptr;
    ClientProtocol::Server *_serverDaemon= nullptr;
    SqlDBCache* _db = nullptr;


    bool payItem(int player, int idItem);
    bool sellItem(int player, int idItem);

    bool restartSrver(const QString& ip, unsigned short port);

private slots:
    void handleRequest(ClientProtocol::Command cmd, const QByteArray &data,
                       const quint32& addres);
    void handleTerminalRequest(QVariantMap obj);

public:
    MainServer(QObject *ptr = nullptr);
    bool run(const QString& ip = "", unsigned short port = 0, const QString &db = "",
             const QString &terminalServer = "", bool terminalForce = false);
    virtual ~MainServer();

};

#endif // SERVER_H
