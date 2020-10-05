#include "Host.h"

Host::Host()
{
    m_LastClient = nullptr;
}

void Host::Init()
{
    for (uint8_t i = 0; i < m_MsgBuffer.size(); i++)
        m_MsgBuffer[i].clientId = i;

    while (!UDP.begin(HOST_PORT))
    {
        Serial.println("UDP setup unsuccessful");
        delay(250);
    }

    Serial.println("UDP setup successful");
}

int Host::SendMessage(UDPMessage *message, UDPClient &client)
{
    if (UDP.beginPacket(client.ip, CLIENT_PORT))
    {
        client.lastSent = millis();
        UDP.write((uint8_t *)message, sizeof(UDPMessage));
        return UDP.endPacket();
    }
    return 0;
}

int Host::RespondToClient(UDPMessage *message)
{
    if (!m_LastClient)
        return -1;

    return Host::SendMessage(message, *m_LastClient);
}

UDPMessage *Host::ReadMessage()
{
    uint8_t packetSize = UDP.parsePacket();
    if (packetSize)
    {
        IPAddress ip = UDP.remoteIP();
        uint8_t clientId;
        uint16_t nBytesRead = UDP.read(&clientId, 1);

        if (nBytesRead)
        {
            if (clientId < clients.size())
            {
                Serial.printf("Message received from %d, elapsed: %d\n", clientId, millis() - clients[clientId].lastReceived);

                clients[clientId].lastReceived = millis();
                clients[clientId].ip = ip;
                m_LastClient = &clients[clientId];
                return &m_MsgBuffer[clientId];
            }
            else
            {
                Serial.println("Invalid id");
                m_LastClient = nullptr;
            }
        }
    }
    return nullptr;
}

UDPMessage *Host::PeekMessage()
{
    for (uint8_t i = 0; i < m_MsgBuffer.size(); i++)
    {
        if (clients[i].IsConnected() && (uint32_t)(millis() - clients[i].lastSent) > m_MsgBuffer[i].requestNextFrameMs)
            return &m_MsgBuffer[i];
    }
    return nullptr;
}
