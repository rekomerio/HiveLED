#include "UDPHost.h"

UDPHost::UDPHost()
{
    m_LastClient = nullptr;
    m_NextMessageIndex = 0;
}

void UDPHost::Init()
{
    for (uint8_t i = 0; i < m_MsgBuffer.size(); i++)
        m_MsgBuffer[i].clientId = i;

    while (!UDP.begin(HOST_PORT))
    {
        Serial.println("UDP setup unsuccessful");
        delay(250);
    }
    delay(256); // Delay so clients cant be seen as connected
    Serial.println("UDP setup successful");
}

int UDPHost::SendMessage(UDPMessage *message, UDPClient &client)
{
    if (UDP.beginPacket(client.ip, CLIENT_PORT))
    {
        client.lastSent = millis();
        UDP.write((uint8_t *)message, sizeof(UDPMessage));
        return UDP.endPacket();
    }
    return 0;
}

int UDPHost::RespondToClient(UDPMessage *message)
{
    if (!m_LastClient)
        return -1;

    return UDPHost::SendMessage(message, *m_LastClient);
}

UDPMessage *UDPHost::ReadMessage()
{
    uint8_t packetSize = UDP.parsePacket();
    if (packetSize)
    {
        IPAddress ip = UDP.remoteIP();
        uint8_t clientId;
        uint16_t nBytesRead = UDP.read(&clientId, 1);

        if (nBytesRead)
        {
            if (clientId < clients.size() || !ip.v4())
            {
                //Serial.printf("Message received from %d, elapsed: %d\n", clientId, millis() - clients[clientId].lastReceived);
                clients[clientId].lastReceived = millis();
                clients[clientId].ip = ip;
                m_LastClient = &clients[clientId];
                return &m_MsgBuffer[clientId];
            }
            else
            {
                Serial.printf("Invalid message from id: %d\n", clientId);
                m_LastClient = nullptr;
            }
        }
    }
    return nullptr;
}

UDPMessage *UDPHost::PeekMessage()
{
    uint8_t &i = m_NextMessageIndex;
    ++i %= clients.size();

    if (clients[i].IsConnected() && (uint32_t)(millis() - clients[i].lastSent) > m_MsgBuffer[i].requestNextFrameMs)
        return &m_MsgBuffer[i];

    return nullptr;
}
