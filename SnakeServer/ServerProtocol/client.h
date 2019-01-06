#ifndef CLIENT_H
#define CLIENT_H
#include "serverprotocol.h"
#include "serverprotocol_global.h"
#include <QObject>

class QLocalSocket;

namespace ServerProtocol {

class SERVERPROTOCOLSHARED_EXPORT Client : public QObject
{
    Q_OBJECT
private:
    QLocalSocket *_destination;
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


#endif // CLIENT_H
