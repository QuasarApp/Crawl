#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <config.h>

#define SERVER_ADDRESS "SERVER_ADDRESS"
#define SERVER_ADDRESS_PORT "SERVER_ADDRESS_PORT"

#define SERVER_ADDRESS_DEFAULT "178.124.160.6"
#define SERVER_ADDRESS_DEFAULT_PORT DEFAULT_SNAKE_PORT

class Settings
{
public:
    Settings() = delete;
    static QSettings *instans();
};

#endif // SETTINGS_H
