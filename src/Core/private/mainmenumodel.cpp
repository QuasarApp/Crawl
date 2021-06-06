#include "mainmenumodel.h"
#include "settingsviewmodel.h"

#include <quasarapp.h>

MainMenuModel::MainMenuModel(QObject *ptr): QObject (ptr) {

    _conf = QuasarAppUtils::Settings::instance();
    _userSettingsModel = new SettingsViewModel(this);

}

QObject *MainMenuModel::userSettingsModel() const {
    return _userSettingsModel;
}
