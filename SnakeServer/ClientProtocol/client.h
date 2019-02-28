#ifndef CLIENT_CP_H
#define CLIENT_CP_H

#include "clientprotocol_global.h"
#include "clientprotocol.h"
#include <QObject>

class QTcpSocket;
class Player;
class BaseItem;

namespace ClientProtocol {


class CLIENTPROTOCOLSHARED_EXPORT Client: public QObject
{
    Q_OBJECT
private:
    QTcpSocket *_destination;
    Package _downloadPackage;
    bool _online = false;
    QByteArray _token;

    void receiveData(const QVariantMap& map);

private slots:
    void incommingData();

public:
    explicit Client(QObject * ptr = nullptr);
    bool sendPackage(const Package& pkg);


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
    bool savaData(QVariantMap gameData);

    /**
     * @brief getItem
     * @param id of item
     * @return item data
     */
    bool getItem(int id);

    /**
     * @brief isOnline
     * @return true if player online
     */
    bool isOnline() const;

signals:
    void sigIncommingData(const QVariantMap& map);
    void onlineChanged(bool);

};

}
#endif // CLIENT_CP_H
