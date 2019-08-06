#ifndef CLIENT_H
#define CLIENT_H

#include "playerclientdata.h"

#include <client.h>

class NetworkClient : public ClientProtocol::Client
{
    Q_OBJECT
private:
    QHash<int, PlayerClientData> _playersDats;
    int _loginedPlayer;
private slots:
    void handleReceiveData(ClientProtocol::Command cmd, const QByteArray& obj);
public:
    NetworkClient();
    int loginedPlayer() const;
};

#endif // CLIENT_H
