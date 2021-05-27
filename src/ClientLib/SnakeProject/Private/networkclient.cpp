#include "networkclient.h"
#include "playerclientdata.h"

#include <updateplayerdata.h>

int NetworkClient::loginedPlayer() const {
    return _loginedPlayer;
}

void NetworkClient::handleReceiveData(ClientProtocol::Command cmd,
                                      const QByteArray &obj) {

    if (cmd == ClientProtocol::Command::Player) {
        PlayerClientData data;
        data.fromBytes(obj);
        _playersDats[data.id()] = data;
    }

}

NetworkClient::NetworkClient() {

}
