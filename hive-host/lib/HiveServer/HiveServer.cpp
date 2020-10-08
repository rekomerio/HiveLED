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

        HandleBinaryMessage(connection, payload, length);
    }
}

void HiveServer::HandleBinaryMessage(uint8_t connection, uint8_t *payload, size_t length)
{
    uint8_t command = payload[0];
    uint8_t clientId = payload[1];
    uint8_t param = payload[2];
    uint16_t value = payload[4] << 8 | payload[3];

    Serial.printf("command %d\n", command);
    Serial.printf("client %d\n", clientId);
    Serial.printf("param %d\n", param);
    Serial.printf("value %d\n", value);

    if (!handler)
        return;

    if (clientId >= MAX_CLIENTS)
        return;

    char msg[64];

    switch (command)
    {
    case Command::SET_PARAM_VALUE:
        handler->SetParam(clientId, (Param)param, value);
        break;
    case Command::GET_PARAM_VALUE:
        ws.sendBIN(connection, (uint8_t *)&handler->GetParam(clientId, (Param)param), 2);
        break;
    case Command::GET_PARAM_NAME:
        break;
    case Command::GET_EFFECT_NAME:
    {
        const char *name = handler->effects[param % handler->effects.size()]->GetName();
        strcpy(msg, name);
        uint8_t index = handler->effects[param % handler->effects.size()]->GetIndex();
        msg[strlen(name)] = ';';
        strcpy(&msg[strlen(name) + 1], String(index).c_str());
        ws.sendTXT(connection, msg);
        break;
    }
    case Command::GET_CLIENT_STATUS:
        break;
    case Command::GET_NUM_PARAMS:
    {
        uint8_t nParams = LEDParams::GetNumParams();
        ws.sendBIN(connection, &nParams, 1);
        break;
    }
    case Command::GET_NUM_EFFECTS:
    {
        uint8_t nEffects = handler->effects.size();
        ws.sendBIN(connection, &nEffects, 1);
        break;
    }
    }
}

void HiveServer::m_OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length)
{
    HiveServer::GetInstance()->OnWebSocketEvent(connection, type, payload, length);
}