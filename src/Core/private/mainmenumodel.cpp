//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <listviewmodel.h>
#include "mainmenumodel.h"
#include "settingsviewmodel.h"

#include <quasarapp.h>

namespace CRAWL {

MainMenuModel::MainMenuModel(QObject *ptr): QObject (ptr) {

    _conf = QuasarAppUtils::Settings::instance();
    _userSettingsModel = new SettingsViewModel(this);
    _availableLvlsModel = new ViewSolutions::ListViewModel(this);

}

QObject *MainMenuModel::userSettingsModel() const {
    return _userSettingsModel;
}

QObject *MainMenuModel::availableLvlsModel() const {
    return _availableLvlsModel;
}

void MainMenuModel::addWorldViewModel(QObject * data) {
    _availableLvlsModel->addSource(data);
}

void MainMenuModel::setAvailableLvls(const QList<QObject*> &newData) {
    _availableLvlsModel->setSource(newData);
}

void MainMenuModel::changeLevel(int lvl) {
    emit sigLevelChanged(lvl);
}

}
