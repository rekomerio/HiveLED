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
        if (strcmp(reinterpret_cast<const char *>(payload), "status") == 0)
        {
            ws.sendTXT(connection, "Status is good");
        }
        break;
    case WStype_BIN:

        for (size_t i = 0; i < length; i++)
        {
            Serial.println(payload[i]);
        }

        if (length < 6)
        {
            Serial.println("Message is too short");
            ws.sendTXT(connection, "Message is too short");
            return;
        }

        if (length > 6)
        {
            Serial.println("Message is too long");
            ws.sendTXT(connection, "Message is too long");
            return;
        }

        uint8_t clientId = payload[0];
        uint8_t command = payload[1];
        uint32_t value = payload[5] << 24 | payload[4] << 16 | payload[3] << 8 | payload[2];

        Serial.printf("client %d\n", clientId);
        Serial.printf("command %d\n", command);
        Serial.printf("value %d\n", value);

        if (!handler)
            return;

        if (clientId >= MAX_CLIENTS)
            return;

        switch (command)
        {
        case 0:
            handler->GetParams(clientId)->activeEffect = (uint8_t)value;
            break;

        default:
            break;
        }
        // TODO: Messaging protocol
        // Required info: client id - 1 byte
        // Param to edit number - 1 byte
        // Param value - 4 bytes
        break;
    }
}

void HiveServer::m_OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length)
{
    HiveServer::GetInstance()->OnWebSocketEvent(connection, type, payload, length);
}