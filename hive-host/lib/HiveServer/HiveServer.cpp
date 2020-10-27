#include "HiveServer.h"

HiveServer::HiveServer() : ws(WebSocketsServer(81))
{
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