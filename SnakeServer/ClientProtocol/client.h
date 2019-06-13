#ifndef CLIENT_CP_H
#define CLIENT_CP_H

#include "clientprotocol_global.h"
#include "clientprotocol.h"
#include <QObject>

class QTcpSocket;
class Player;
class BaseItem;
class testSankeServer;

namespace ClientProtocol {


class CLIENTPROTOCOLSHARED_EXPORT Client: public QObject
{
    Q_OBJECT
private:
    QTcpSocket *_destination;
    Package _downloadPackage;
    bool _online = false;
    bool _logined = false;
    QByteArray _token;
    QByteArray _rsaKey;
    int currentIndex = 0;
    QHash<unsigned char, QVariantMap> _requestsMap;

    bool receiveData(const QByteArray &obj, Header hdr);
    bool setRSAKey(const QByteArray &key);
    void setLoginStatus(bool newStatus);

    bool sendPackage(Package &pkg);
    inline unsigned char nextIndex();

    bool ping();


private slots:
    void incommingData();

public:
    explicit Client(const QString& addrress = LOCAL_SNAKE_SERVER,
                    unsigned short port = DEFAULT_SNAKE_PORT,
                    QObject * ptr = nullptr);


    /**
     * @brief login - register or login a user
     * @param gmail - gmail of user
     * @param pass - hash of pass of user
     * @param error - error ( if all good this variable is empty)
     * @return
     */
    bool login(const QString& gmail, const QByteArray &pass);

    /**
     * @brief updateData
     * @return  true if refresh seсcessfully completed
     */
    bool updateData();

    /**
     * @brief savedata
     * @param gameData - data of lvl
     * @return true if all good
     */
    bool savaData(const QList<int> &gameData);

    /**
     * @brief getItem
     * @param id of item
     * @return item data
     */
    bool getItem(int id);

    /**
     * @brief isOnline
     * @return true if client is connected to server and get rsapub key
     */
    const bool &isOnline() const;

    /**
     * @brief isLogin
     * @return true if player is online
     */
    const bool &isLogin() const;

    friend class ::testSankeServer;

signals:
    void sigIncommingData(Command cmd, const QByteArray& obj);
    void onlineChanged(bool);
    void loginChanged(bool);

};

}
#endif // CLIENT_CP_H
