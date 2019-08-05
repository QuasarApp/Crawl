#ifndef NETWORKPROFILEMAINMODEL_H
#define NETWORKPROFILEMAINMODEL_H

#include <QObject>
#include <QSettings>

class UserView;

namespace ClientProtocol {
    class Client;
}

enum OnlineStatus: int {
    Success = 0x0,
    AuthorizationRequired,
    WaitForAnswer,
    AuthorizationFail,
    ClientIsOffline
};

class MainMenuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* userViewModel READ userViewModel NOTIFY userViewModelChanged)
    Q_PROPERTY(int onlineStatus READ onlineStatus WRITE setOnlineStatus NOTIFY onlineStatusChanged)

private:
    UserView* _userViewModel = nullptr;
    ClientProtocol::Client *_client = nullptr;
    OnlineStatus _onlineStatus = ClientIsOffline;
    QSettings *_conf = nullptr;

private slots:
    void handleClientStatusChanged(bool);

public:
    MainMenuModel(QObject *ptr = nullptr);

    QObject* userViewModel() const;
    int onlineStatus() const;

public slots:
    void setOnlineStatus(int onlineStatus);
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
