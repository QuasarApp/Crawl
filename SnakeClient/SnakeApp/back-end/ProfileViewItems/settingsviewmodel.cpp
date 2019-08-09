#include "settingsviewmodel.h"
#include <QSettings>
#include "settings.h"

void SettingsViewModel::handleValueChanged(QString key, QVariant value) {
    if (key == SERVER_ADDRESS) {
        emit hostChanged(value.toString());
    } else if (key == SERVER_ADDRESS_PORT) {
        emit portChanged(value.toInt());
    } else if (key == THEME) {
        emit themeChanged(value.toInt());
    }
}

SettingsViewModel::SettingsViewModel(QObject *ptr):
    QObject (ptr) {
    _cfg = Settings::get();

    connect(_cfg, &Settings::valueChanged, this , &SettingsViewModel::handleValueChanged);
}

int SettingsViewModel::port() const {
    return _cfg->getValue(SERVER_ADDRESS_PORT, SERVER_ADDRESS_DEFAULT_PORT).toInt();
}

QString SettingsViewModel::host() const {
    return _cfg->getValue(SERVER_ADDRESS, SERVER_ADDRESS_DEFAULT).toString();
}

int SettingsViewModel::theme() const {
    return _cfg->getValue(THEME, THEME_DEFAULT).toInt();
}

void SettingsViewModel::forceUpdate() {
    emit hostChanged("");
    emit portChanged(0);
    emit themeChanged(0);

}

void SettingsViewModel::toDefault() {
    setPort(SERVER_ADDRESS_DEFAULT_PORT);
    setHost(SERVER_ADDRESS_DEFAULT);
    setTheme(THEME_DEFAULT);
}

void SettingsViewModel::setPort(int port) {
    _cfg->setValue(SERVER_ADDRESS_PORT, port);
}

void SettingsViewModel::setHost(const QString& host) {
    _cfg->setValue(SERVER_ADDRESS, host);
}

void SettingsViewModel::setTheme(int theme) {
    _cfg->setValue(THEME, theme);
}
