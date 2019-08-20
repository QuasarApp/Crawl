#include "mainclient.h"
#include "notificationservice.h"
#include "playerclientdata.h"

#include <QSharedPointer>

OnlineStatus MainClient::onlineStatus() const {
    return _onlineStatus;
}

void MainClient::setOnlineStatus(OnlineStatus onlineStatus) {
    if (_onlineStatus == onlineStatus)
        return;

    emit sigOnlineStatusChanged(_onlineStatus = onlineStatus);
    pushNotify(onlineStatus);

}

void MainClient::clientStatusChanged() {
    auto  status = OnlineStatus::ClientIsOffline;

    if (isOnline()) {
        status = OnlineStatus::AuthorizationRequired;
    }

    if (isLogin()) {
        status = OnlineStatus::Success;
    }

    setOnlineStatus(status);
}

void MainClient::pushNotify(OnlineStatus onlineStatus) {


    switch (onlineStatus) {

    case 0: {

        NotificationService::getService()->setNotify(
                    NotificationData(tr("Login status"), tr("Success")));

        break;
    }

//    case 1: {

//        NotificationService::getService()->setNotify(
//                    NotificationData(tr("Login status"), tr("Authorization Required")));

//        break;
//    }

//    case 2: {

//        NotificationService::getService()->setNotify(
//                    NotificationData(tr("Login status"), tr("Wait for answer")));

//        break;
//    }

    case 3: {

        NotificationService::getService()->setNotify(
                    NotificationData(tr("Login result"), tr("Authorization fail") ,  "", NotificationData::Error));

        break;
    }

    case 4: {

        NotificationService::getService()->setNotify(
                    NotificationData(tr("Login result"), tr("Client is offline"), "", NotificationData::Warning));

        break;
    }

    case 5: {

        NotificationService::getService()->setNotify(
                    NotificationData(tr("Login result"), tr("Offline Mode")));

        break;
    }

    default: break;

    }
}

void MainClient::handleReceivePackage(ClientProtocol::Command cmd, const QByteArray &obj) {
    switch (cmd) {

    case ClientProtocol::Command::Player: {
        auto playerData =  QSharedPointer<PlayerClientData>::create();
        playerData->fromBytes(obj);

        _users [playerData->id()] = playerData;

        if (playerData->id() == _currentUserId) {
            emit currentUserDataChanged(_users [playerData->id()]);
        }

        break;
    }

    case ClientProtocol::Command::BadRequest: {

        break;
    }
    default: return;
    }
}

void MainClient::handleLoginChanged(bool logined) {
    this->setSubscribe(ClientProtocol::Command::Player, logined, _currentUserId);
    clientStatusChanged();

}

void MainClient::handleOnlineChanged(bool) {
    clientStatusChanged();
}

MainClient::MainClient(const QString &addrress, unsigned short port, QObject *ptr):
    ClientProtocol::Client (addrress, port, ptr) {

    connect(this, &MainClient::sigIncommingData,
            this, &MainClient::handleReceivePackage);

    connect(this, &MainClient::onlineChanged,
            this, &MainClient::handleOnlineChanged);

    connect(this, &MainClient::loginChanged,
            this, &MainClient::handleLoginChanged);
}

bool MainClient::login(const QString &gmail, const QByteArray &pass, bool) {
    if (!ClientProtocol::Client::login(gmail, pass)) {
        setOnlineStatus(OnlineStatus::AuthorizationFail);
        return false;
    }

    return true;
}

bool MainClient::registration(const QString &gmail,
                              const QByteArray &pass) {

    if (!ClientProtocol::Client::registration(gmail, pass)) {
        setOnlineStatus(OnlineStatus::AuthorizationFail);
        return false;
    }

    return true;
}

void MainClient::playOffline() {
    if (_onlineStatus == OnlineStatus::ClientIsOffline) {
        setOnlineStatus(OfflineMode);
    }
}

void MainClient::tryConnect(const QString &addrress, unsigned short port) {
    setOnlineStatus(ClientIsOffline);
    connectToHost(addrress, port);
}

MainClient::~MainClient() {
    for (auto &i: _users) {
        i.clear();
    }
    _users.clear();
}
