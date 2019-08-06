#include "mainmenumodel.h"
#include "userview.h"

#include <client.h>

#include <back-end/settings.h>
#include <quasarapp.h>

void MainMenuModel::handleClientStatusChanged(bool) {
    auto  status = OnlineStatus::ClientIsOffline;
    if (_client->isOnline()) {
        status = OnlineStatus::AuthorizationRequired;
    }

    if (_client->isLogin()) {
        status = OnlineStatus::Success;
    }

    setOnlineStatus(status);
}

MainMenuModel::MainMenuModel(QObject *ptr): QObject (ptr) {

    if(!ClientProtocol::initClientProtockol()) {
        QuasarAppUtils::Params::verboseLog("client protockol not inited", QuasarAppUtils::Error);
    }

    _userViewModel = new UserView (this);
    _conf = Settings::instans();

    auto adderss = _conf->value(SERVER_ADDRESS, SERVER_ADDRESS_DEFAULT).toString();
    auto port = _conf->value(SERVER_ADDRESS_PORT, SERVER_ADDRESS_DEFAULT_PORT).toInt();
    _client = new ClientProtocol::Client(adderss, static_cast<unsigned short>(port), this);

    connect(_client, &ClientProtocol::Client::loginChanged,
            this , &MainMenuModel::handleClientStatusChanged);

    connect(_client, &ClientProtocol::Client::onlineChanged,
            this , &MainMenuModel::handleClientStatusChanged);

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

void MainMenuModel::login(const QString &email, const QString &pass) {
    if (!_client->login(email, pass.toUtf8())) {
        setOnlineStatus(OnlineStatus::AuthorizationFail);
    }
}

void MainMenuModel::registerNewUser(const QString &email, const QString &name,
                                    const QString &pass) {
    if (!_client->login(email, pass.toUtf8())) {
        setOnlineStatus(OnlineStatus::AuthorizationFail);
    }
}
