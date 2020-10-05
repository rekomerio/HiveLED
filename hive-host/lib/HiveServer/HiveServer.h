#include <WebSocketsServer.h>
#include "MessageHandler.h"

class HiveServer
{
public:
    static HiveServer *GetInstance();
    void Init();
    void Update();
    MessageHandler *handler;

private:
    HiveServer();

    void OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length);
    static void m_OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length);

    WebSocketsServer ws;
};