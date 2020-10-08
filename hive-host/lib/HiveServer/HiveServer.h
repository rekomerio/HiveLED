#include <WebSocketsServer.h>
#include "MessageHandler.h"

class HiveServer
{
public:
    enum Command : uint8_t
    {
        SET_PARAM_VALUE,
        GET_PARAM_VALUE,
        GET_PARAM_NAME,
        GET_EFFECT_NAME,
        GET_CLIENT_STATUS,
        GET_NUM_PARAMS,
        GET_NUM_EFFECTS
    };

    static HiveServer *GetInstance();
    void Init();
    void Update();
    void HandleWSRoute();
    void HandleBinaryMessage(uint8_t connection, uint8_t *payload, size_t length);

    MessageHandler *handler;

private:
    HiveServer();

    void OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length);
    static void m_OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length);

    WebSocketsServer ws;
};