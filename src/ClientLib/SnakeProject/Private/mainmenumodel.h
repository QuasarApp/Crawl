#ifndef NETWORKPROFILEMAINMODEL_H
#define NETWORKPROFILEMAINMODEL_H

#include <QObject>
#include "snakeprojectsettings.h"


class MainMenuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* userSettingsModel READ userSettingsModel NOTIFY userSettingsModelChanged)

private:
    Settings *_conf = nullptr;

public:
    MainMenuModel(QObject *ptr = nullptr);
    QObject* userSettingsModel() const;

signals:
    void userSettingsModelChanged(QObject* userSettingsModel);
};

#endif // NETWORKPROFILEMAINMODEL_H
