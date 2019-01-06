#ifndef SARVERDAEMON_H
#define SARVERDAEMON_H
#include <server.h>
#include <serverprotocol.h>

class SarverDaemon
{
private:
    ServerProtocol::Server localServer;
public:
    SarverDaemon();
};

#endif // SARVERDAEMON_H
