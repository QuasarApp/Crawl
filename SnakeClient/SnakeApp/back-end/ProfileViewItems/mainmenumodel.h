#ifndef NETWORKPROFILEMAINMODEL_H
#define NETWORKPROFILEMAINMODEL_H

#include "mainclient.h"

#include <QObject>
#include "./../settings.h"

class UserView;

class MainClient;
class SettingsViewModel;

class MainMenuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* userViewModel READ userViewModel NOTIFY userViewModelChanged)
    Q_PROPERTY(QObject* userSettingsModel READ userSettingsModel NOTIFY userSettingsModelChanged)

    Q_PROPERTY(int onlineStatus READ onlineStatus NOTIFY onlineStatusChanged)

private:
    UserView* _userViewModel = nullptr;
    SettingsViewModel* _userSettingsModel = nullptr;
    MainClient *_client = nullptr;
    Settings *_conf = nullptr;

public:
    MainMenuModel(QObject *ptr = nullptr);

    QObject* userViewModel() const;
    QObject* userSettingsModel() const;

    int onlineStatus() const;
    Q_INVOKABLE void playOffline();
    Q_INVOKABLE void tryConnect();


public slots:
    void login(const QString& email, const QString& pass);
    void registerNewUser(const QString& email, const QString& pass);


signals:
    void userViewModelChanged(QObject* userViewModel);
    void newGame();

    void onlinelChanged(bool online);
    void loginChanged(bool login);
    void onlineStatusChanged();
    void userSettingsModelChanged(QObject* userSettingsModel);
};

#endif // NETWORKPROFILEMAINMODEL_H
