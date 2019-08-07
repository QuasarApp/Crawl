#ifndef MAINCLIENT_H
#define MAINCLIENT_H
#include <client.h>

class PlayerClientData;

class MainClient: public ClientProtocol::Client
{
    Q_OBJECT
private:
    QHash<int, QSharedPointer<PlayerClientData>> _users;
private slots:
    void handleReceivePackage(ClientProtocol::Command cmd, const QByteArray& obj);
    void handleLoginChanged(bool);
    void handleOnlineChanged(bool);

public:
    MainClient();
    ~MainClient();

};

#endif // MAINCLIENT_H
