#ifndef WEBSOCKETCONTROLLER_H
#define WEBSOCKETCONTROLLER_H
#include <QObject>
#include <QMultiHash>
#include <clientprotocol.h>

class Item;
class PlayerDBData;

namespace ClientProtocol {
    class Server;
}

class WebSocketController: public QObject
{
    Q_OBJECT
private:
    QMultiHash<char, quint32> _subscribs;
    ClientProtocol::Server *_serverDaemon = nullptr;

public:
    WebSocketController(ClientProtocol::Server * server, QObject* obj = nullptr);
    void subscribe(quint32 address, ClientProtocol::Command cmd);
    void unsubscribe(quint32 address, ClientProtocol::Command cmd);
public slots:
    void handleItemChanged(int id, const Item& newData);
    void handlePlayerChanged(int id, const PlayerDBData& newData);

};

#endif // WEBSOCKETCONTROLLER_H
