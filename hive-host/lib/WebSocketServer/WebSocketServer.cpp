#include "WebSocketServer.h"

WebSocketServer::WebSocketServer() : ws(WebSocketsServer(81))
{
}

void WebSocketServer::Init()
{
    ws.onEvent(m_OnWebSocketEvent);
    ws.begin();
}

void WebSocketServer::Update()
{
    ws.loop();
}

WebSocketServer *WebSocketServer::GetInstance()
{
    static WebSocketServer *instance = new WebSocketServer();
    return instance;
}

void WebSocketServer::OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length)
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
        // for (size_t i = 0; i < length; i++)
        //     Serial.println(payload[i]);

        HandleBinaryMessage(connection, payload, length);
        break;
    }
}

void WebSocketServer::HandleBinaryMessage(uint8_t connection, uint8_t *payload, size_t length)
{
    uint8_t command = payload[0];
    uint8_t clientId = payload[1];
    uint8_t param = payload[2];
    uint16_t value = payload[4] << 8 | payload[3];

    // Serial.printf("command %d\n", command);
    // Serial.printf("client %d\n", clientId);
    // Serial.printf("param %d\n", param);
    // Serial.printf("value %d\n", value);

    switch (command)
    {
    case Command::SET_PARAM_VALUE:
        messageHandler.SetParam(clientId, (Param)param, value);
        break;
    case Command::GET_PARAM_VALUE:
        ws.sendBIN(connection, (uint8_t *)&messageHandler.GetParam(clientId, (Param)param), 1);
        break;
    case Command::GET_EFFECTS:
        ws.sendTXT(connection, messageHandler.GetEffectsJSON());
        break;
    case Command::GET_PARAMS:
        ws.sendTXT(connection, messageHandler.GetParamsJSON(clientId));
        break;
    case Command::GET_CLIENTS:
        ws.sendTXT(connection, messageHandler.GetClientsJSON());
        break;
    }
}

void WebSocketServer::m_OnWebSocketEvent(uint8_t connection, WStype_t type, uint8_t *payload, size_t length)
{
    WebSocketServer::GetInstance()->OnWebSocketEvent(connection, type, payload, length);
}