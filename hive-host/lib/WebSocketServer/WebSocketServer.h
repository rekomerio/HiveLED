#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <WebSocketsServer.h>
#include "MessageHandler.h"

class WebSocketServer
{
public:
    enum Command : uint8_t
    {
        SET_PARAM_VALUE,
        GET_PARAM_VALUE,
        GET_EFFECTS,
        GET_PARAMS,
        GET_CLIENTS,
    };

    static WebSocketServer *GetInstance();
    void Init();
    void Update();

private:
    WebSocketServer();

    void HandleWSRoute();
    void HandleBinaryMessage(uint8_t connection, uint8_t *payload, size_t length);
    void OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length);
    static void m_OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length);

    WebSocketsServer ws;
};

#endif