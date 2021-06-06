#ifndef NETWORKPROFILEMAINMODEL_H
#define NETWORKPROFILEMAINMODEL_H

#include <QObject>
#include "settings.h"


class MainMenuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* userSettingsModel READ userSettingsModel NOTIFY userSettingsModelChanged)

private:
    Settings *_conf = nullptr;
    QObject* _userSettingsModel = nullptr;

public:
    MainMenuModel(QObject *ptr = nullptr);
    QObject* userSettingsModel() const;

signals:
    void userSettingsModelChanged(QObject* userSettingsModel);
    void newGame();
};

#endif // NETWORKPROFILEMAINMODEL_H
