#include "mainmenumodel.h"
#include "userview.h"

MainMenuModel::MainMenuModel(QObject *ptr): QObject (ptr) {
    _userViewModel = new UserView (this);
}

QObject *MainMenuModel::userViewModel() const {
    return _userViewModel;
}

bool MainMenuModel::online() const {
    return false;
}

bool MainMenuModel::login() const {
    return false;
}
