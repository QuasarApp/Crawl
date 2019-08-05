#include "mainmenumodel.h"
#include "userview.h"

#include <client.h>

#include <back-end/settings.h>

MainMenuModel::MainMenuModel(QObject *ptr): QObject (ptr) {
    _userViewModel = new UserView (this);
    _conf = Settings::instans();
    auto adderss = _conf->value(SERVER_ADDRESS, SERVER_ADDRESS_DEFAULT).toString();
    auto port = _conf->value(SERVER_ADDRESS_PORT, SERVER_ADDRESS_DEFAULT_PORT).toInt();
    _client = new ClientProtocol::Client(adderss, static_cast<unsigned short>(port), this);
}

QObject *MainMenuModel::userViewModel() const {
    return _userViewModel;
}

int MainMenuModel::onlineStatus() const {
    return _onlineStatus;
}

void MainMenuModel::setOnlineStatus(int onlineStatus) {
    if (_onlineStatus == onlineStatus)
        return;

    _onlineStatus = static_cast<OnlineStatus>(onlineStatus);
    emit onlineStatusChanged();
}
