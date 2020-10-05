#include "HiveServer.h"

HiveServer::HiveServer() : ws(WebSocketsServer(81))
{
    handler = nullptr;
}

void HiveServer::Init()
{
    ws.onEvent(m_OnWebSocketEvent);
    ws.begin();
}

void HiveServer::Update()
{
    ws.loop();
}

HiveServer *HiveServer::GetInstance()
{
    static HiveServer *instance = new HiveServer();
    return instance;
}

void HiveServer::OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.printf("[%u] Disconnected!\n", connection);
        break;
    case WStype_CONNECTED:
    {
        IPAddress ip = ws.remoteIP(connection);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", connection, ip[0], ip[1], ip[2], ip[3], payload);

        ws.sendTXT(connection, "Connected");
    }
    break;
    case WStype_TEXT:
        Serial.printf("[%u] get Text: %s\n", connection, payload);

        if (handler)
            for (auto &effect : handler->effects)
                effect.params.activeEffect++;
    }
}

void HiveServer::m_OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length)
{
    HiveServer::GetInstance()->OnWebSocketEvent(connection, type, payload, length);
}