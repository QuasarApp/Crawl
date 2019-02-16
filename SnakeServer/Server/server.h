#ifndef SERVER_H
#define SERVER_H
#include <serverprotocol.h>
#include "server_global.h"

namespace ServerProtocol {
    class Server;
}

class SERVERSHARED_EXPORT Server: public QObject
{
    Q_OBJECT
private:
    ServerProtocol::Server *_serverDaemon = nullptr;

public:
    Server(QObject *ptr = nullptr);
    virtual ~Server();
};

#endif // SERVER_H
