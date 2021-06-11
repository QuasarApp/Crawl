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
