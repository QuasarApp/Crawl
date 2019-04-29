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

struct Connectioninfo {

    QTcpSocket *sct;
    int karma;

    Connectioninfo(QTcpSocket * tcp = nullptr,
                   int kar = NOT_VALID_CARMA);
    ~Connectioninfo();

};

class CLIENTPROTOCOLSHARED_EXPORT Server : public QTcpServer
{
    Q_OBJECT
private:
    Package _downloadPackage;
    QHash<quint32, Connectioninfo> _connections;
//    QHash<quint32, int> _karma;

    bool parsePackage(const Package &pkg, QTcpSocket * sender);
    bool sendPackage(Package &pkg, QTcpSocket * target);
    void registerSocket(QTcpSocket *socket);
    bool changeKarma(quint32 addresss, int diff);
    inline bool isBaned(const QTcpSocket *) const;
    void saveKarma() const;
    bool loadKarma();

private slots:
    void avelableBytes();
    void handleIncommingConnection();

public:
    explicit Server(QObject * ptr = nullptr);
    ~Server() override;
    bool run(const QString& ip, unsigned short port);
    void stop(bool reset = false);

    void badRequest(quint32 address);

    void ban(quint32 target);
    void unBan(quint32 target);

    /**
     * @brief getWorkState
     * @return string of work state
     */
    QString getWorkState() const;

    /**
     * @brief connectionState
     * @return string with count users state
     */
    QString connectionState() const;

    QStringList baned() const;
signals:
    void incomingReques(BaseNetworkObject *map, const quint32 &sender);
};

}
#endif // SERVER_CP_H
