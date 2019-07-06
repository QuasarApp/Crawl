#include "websocketcontroller.h"

WebSocketController::WebSocketController(ClientProtocol::Server *server, QObject* obj):
    QObject (obj) {

    assert( server );
    _serverDaemon = server;
}

void WebSocketController::subscribe(quint32 address, ClientProtocol::Command cmd) {
    _subscribs.insertMulti(static_cast<char>(cmd), address);
}

void WebSocketController::unsubscribe(quint32 address, ClientProtocol::Command cmd) {
    _subscribs.remove(static_cast<char>(cmd), address);
}

void WebSocketController::handleItemChanged(int id, const Item &newData) {

}

void WebSocketController::handlePlayerChanged(int id, const PlayerDBData &newData) {

}
