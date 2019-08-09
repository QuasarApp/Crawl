#include "settings.h"

QSettings *Settings::instans() {
    static QSettings* data = new QSettings();
    return data;
}
