#ifndef SERVER_H
#define SERVER_H
#include <serverprotocol.h>
#include "server_global.h"
#include <QHostAddress>

namespace ServerProtocol {
    class Server;
}

namespace ClientProtocol {
    class Server;
}

class SERVERSHARED_EXPORT MainServer: public QObject
{
    Q_OBJECT
private:
    ServerProtocol::Server *_terminalPort = nullptr;
    ClientProtocol::Server *_serverDaemon= nullptr;

    bool payItem(int player, int idItem);
    bool sellItem(int player, int idItem);

    bool restartSrver(const QString& ip, unsigned short port);

private slots:
    void handleRequest(QVariantMap obj, const QHostAddress& addres);
    void handleTerminalRequest(QVariantMap obj);

public:
    MainServer(QObject *ptr = nullptr);
    bool run();
    virtual ~MainServer();
};

#endif // SERVER_H
