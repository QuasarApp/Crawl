#include "mainmenumodel.h"
#include "userview.h"

MainMenuModel::MainMenuModel(QObject *ptr): QObject (ptr) {
    _userViewModel = new UserView (this);
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
