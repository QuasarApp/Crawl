#include "mainclient.h"
#include "playerclientdata.h"

#include <QSharedPointer>

void MainClient::handleReceivePackage(ClientProtocol::Command cmd, const QByteArray &obj) {
    switch (cmd) {

    case ClientProtocol::Command::Player: {
        auto playerData =  QSharedPointer<PlayerClientData>::create();
        playerData->fromBytes(obj);

        _users [playerData->id()] = playerData;

        break;
    }
    default: return;
    }
}

void MainClient::handleLoginChanged(bool logined) {
    this->setSubscribe(ClientProtocol::Command::Player, logined, _currentUserId);

}

void MainClient::handleOnlineChanged(bool) {

}

MainClient::MainClient() {

    connect(this, &MainClient::sigIncommingData,
            this, &MainClient::handleReceivePackage);

    connect(this, &MainClient::onlineChanged,
            this, &MainClient::handleOnlineChanged);

    connect(this, &MainClient::loginChanged,
            this, &MainClient::handleLoginChanged);
}

MainClient::~MainClient() {
    for (auto &i: _users) {
        i.clear();
    }
    _users.clear();
}
