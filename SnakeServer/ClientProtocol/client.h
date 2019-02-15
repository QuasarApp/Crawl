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
    bool updateData(const QString& gmail, const QByteArray &pass);

    /**
     * @brief getItem
     * @param id of item
     * @return item data
     */
    bool getItem(int id, const QByteArray &pass);


signals:
    void sigIncommingData(const QVariantMap& map);

};

}
#endif // CLIENT_CP_H
