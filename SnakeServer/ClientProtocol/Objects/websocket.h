#ifndef WEBSOCKET_H
#define WEBSOCKET_H
#include "updateplayerdata.h"
#include "clientprotocol.h"

namespace ClientProtocol {

#pragma pack(push, 1)
struct WebSocketData {
    char cmd : 5;
    char subscribe : 5;

    friend QDataStream& operator<< (QDataStream& stream, WebSocketData data);
    friend QDataStream& operator>> (QDataStream& stream, WebSocketData& data);

};
#pragma pack(pop)

class CLIENTPROTOCOLSHARED_EXPORT WebSocket : public UpdatePlayerData
{
    WebSocketData _data;
public:
    WebSocket();

    BaseNetworkObject *create() const override;
    NetworkClassSize classSize() const override;
    QDataStream &writeToStream(QDataStream &stream) const override;
    QDataStream &readFromStream(QDataStream &stream) override;
    bool isValid() const override;

    bool isSubscribe() const;
    Command getCommand() const;

    void setSubscribe(bool subscribe);
    void setCommand(Command cmd) ;
};
}
#endif // WEBSOCKET_H
