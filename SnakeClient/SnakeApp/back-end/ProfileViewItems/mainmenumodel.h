#ifndef NETWORKPROFILEMAINMODEL_H
#define NETWORKPROFILEMAINMODEL_H

#include "mainclient.h"

#include <QObject>
#include <QSettings>

class UserView;

class MainClient;

class MainMenuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* userViewModel READ userViewModel NOTIFY userViewModelChanged)
    Q_PROPERTY(int onlineStatus READ onlineStatus NOTIFY onlineStatusChanged)

private:
    UserView* _userViewModel = nullptr;
    MainClient *_client = nullptr;
    QSettings *_conf = nullptr;

public:
    MainMenuModel(QObject *ptr = nullptr);

    QObject* userViewModel() const;
    int onlineStatus() const;

public slots:
    void login(const QString& email, const QString& pass);
    void registerNewUser(const QString& email, const QString& name, const QString& pass);

signals:
    void userViewModelChanged(QObject* userViewModel);
    void newGame();

    void onlinelChanged(bool online);
    void loginChanged(bool login);
    void onlineStatusChanged();
};

#endif // NETWORKPROFILEMAINMODEL_H
