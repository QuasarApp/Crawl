#ifndef CLIENT_SP_H
#define CLIENT_SP_H
#include "serverprotocol.h"
#include "serverprotocol_global.h"
#include <QObject>
#include <QHostAddress>

class QLocalSocket;

namespace ServerProtocol {

class SERVERPROTOCOLSHARED_EXPORT Client : public QObject
{
    Q_OBJECT
private:
    QLocalSocket *_destination;
    Package _downloadPackage;

    bool sendPackage(const Package& pkg);

private slots:
    void incommingData();

public:
    explicit Client(QObject * ptr = nullptr);
    bool ping();
    bool getState();
    bool ban(const QHostAddress& address);
    bool unBan(const QHostAddress& address);
    bool restart(const QString &address, unsigned short port);
    bool start(const QString &address, unsigned short port);
    bool stop();


signals:
    void sigIncommingData(const QVariantMap& map);
};

}


#endif // CLIENT_SP_H
