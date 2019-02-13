#ifndef CLIENT_CP_H
#define CLIENT_CP_H

#include "clientprotocol_global.h"
#include "clientprotocol.h"
#include <QObject>


class QTcpSocket;

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

signals:
    void sigIncommingData(const QVariantMap& map);

};

}
#endif // CLIENT_CP_H
