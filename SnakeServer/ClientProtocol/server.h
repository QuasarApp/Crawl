#ifndef SERVER_CP_H
#define SERVER_CP_H
#include "clientprotocol_global.h"
#include "clientprotocol.h"

#include <QTcpServer>

namespace ClientProtocol {

#define NOT_VALID_CARMA 0xFF
#define DEFAULT_KARMA   100
#define RESTORE_KARMA   20
#define BANED_KARMA     0

#define CRITICAL_ERROOR -50
#define LOGICK_ERROOR   -20
#define REQUEST_ERROR   -5

class CLIENTPROTOCOLSHARED_EXPORT Server : public QTcpServer
{
    Q_OBJECT
private:
    Package _downloadPackage;
    QHash<QHostAddress, int> karma;

    bool parsePackage(const Package &pkg, QTcpSocket * sender);
    bool sendPackage(Package &pkg, QTcpSocket * target);
    void ban(const QHostAddress &target);
    void unBan(const QHostAddress &target);
    void registerSocket(const QTcpSocket *socket);
    bool changeKarma(const QHostAddress& addresss, int diff);
    inline bool isBaned(const QTcpSocket *) const;

private slots:
    void avelableBytes();
    void handleIncommingConnection();

public:
    explicit Server(QObject * ptr = nullptr);
    ~Server() override;
    bool run(const QString& ip, unsigned short port);

signals:
    void incomingReques(const QVariantMap &map, const QHostAddress &sender);
};

}
#endif // SERVER_CP_H
