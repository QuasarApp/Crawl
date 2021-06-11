#include <listviewmodel.h>
#include "mainmenumodel.h"
#include "settingsviewmodel.h"

#include <quasarapp.h>

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

void MainMenuModel::setAvailableLvls(const QList<QObject*> &newData) {
    _availableLvlsModel->setSource(newData);
}

void MainMenuModel::newGame(const QString &lvl) {
    emit sigNewGame(lvl);
}

