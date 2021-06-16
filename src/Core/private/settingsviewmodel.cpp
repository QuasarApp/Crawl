//#
//# Copyright (C) 2021-2021 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "settingsviewmodel.h"
#include <QSettings>
#include "settings.h"

void SettingsViewModel::handleValueChanged(QString key, QVariant value) {
    if (key == THEME) {
        emit themeChanged(value.toInt());
    }
}

SettingsViewModel::SettingsViewModel(QObject *ptr):
    QObject (ptr) {
    _cfg = Settings::instance();

    connect(_cfg, &Settings::valueChanged, this , &SettingsViewModel::handleValueChanged);
}

int SettingsViewModel::theme() const {
    return _cfg->getValue(THEME, THEME_DEFAULT).toInt();
}

void SettingsViewModel::forceUpdate() {
    emit themeChanged(0);
}

void SettingsViewModel::toDefault() {
    setTheme(THEME_DEFAULT);
}

void SettingsViewModel::setTheme(int theme) {
    _cfg->setValue(THEME, theme);
}
