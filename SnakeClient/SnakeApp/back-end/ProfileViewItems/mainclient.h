#ifndef MAINCLIENT_H
#define MAINCLIENT_H
#include <client.h>

class PlayerClientData;

enum OnlineStatus: int {
    Success = 0x0,
    AuthorizationRequired,
    WaitForAnswer,
    AuthorizationFail,
    ClientIsOffline,
    OfflineMode
};

class MainClient: public ClientProtocol::Client
{
    Q_OBJECT
private:
    QHash<int, QSharedPointer<PlayerClientData>> _users;
    OnlineStatus _onlineStatus = ClientIsOffline;

    void setOnlineStatus(OnlineStatus onlineStatus);
    void clientStatusChanged();


private slots:
    void handleReceivePackage(ClientProtocol::Command cmd, const QByteArray& obj);
    void handleLoginChanged(bool);
    void handleOnlineChanged(bool);

public:
    MainClient(const QString& addrress = LOCAL_SNAKE_SERVER,
               unsigned short port = DEFAULT_SNAKE_PORT,
               QObject * ptr = nullptr);
    bool login(const QString& gmail, const QByteArray &pass, bool registerNewUser = false) override;
    bool registration(const QString& gmail,
                      const QByteArray &pass) override;
    void playOffline();
    void tryConnect(const QString &addrress, unsigned short port);

    ~MainClient() override;

    OnlineStatus onlineStatus() const;

signals:
    void sigOnlineStatusChanged(OnlineStatus);
    void currentUserDataChanged(QSharedPointer<PlayerClientData>);
};

#endif // MAINCLIENT_H
