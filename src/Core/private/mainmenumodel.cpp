//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <listviewmodel.h>
#include "availablelevelsmodel.h"
#include "mainmenumodel.h"
#include "settingsviewmodel.h"
#include "storeviewmodel.h"

#include <quasarapp.h>

namespace CRAWL {

MainMenuModel::MainMenuModel(QObject *ptr): QObject (ptr) {

    _conf = QuasarAppUtils::Settings::instance();
    _userSettingsModel = new SettingsViewModel(this);
    _storeView = new StoreViewModel();
    _selectLevelModle = new AvailableLevelsModel();
}

MainMenuModel::~MainMenuModel() {
    delete _storeView;
    delete _selectLevelModle;
}

QObject *MainMenuModel::userSettingsModel() const {
    return _userSettingsModel;
}

bool MainMenuModel::getVisible() const {
    return visible;
}

void MainMenuModel::setVisible(bool newVisible) {
    if (visible == newVisible)
        return;
    visible = newVisible;
    emit visibleChanged();
}

QObject *MainMenuModel::storeView() const {
    return _storeView;
}

AvailableLevelsModel *MainMenuModel::selectLevelModle() const {
    return _selectLevelModle;
}

}
