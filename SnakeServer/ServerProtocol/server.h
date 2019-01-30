#ifndef SERVER_H
#define SERVER_H
#include "serverprotocol.h"
#include "serverprotocol_global.h"
#include <QLocalServer>

class QLocalSocket;
namespace ServerProtocol {

class SERVERPROTOCOLSHARED_EXPORT Server: public QLocalServer
{
    Q_OBJECT
private:
    QLocalSocket *_client;
    Package _downloadPackage;

    void parsePackage(const Package &pkg);

private slots:
    void avelableBytes();

protected:
    void incomingConnection(quintptr socketDescriptor);
public:
    explicit Server(QObject * ptr = nullptr);
    bool run(const QString& name);
};
}
#endif // SERVER_H
