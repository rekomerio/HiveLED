#include "Host.h"

Host::Host()
{
    m_LastClient = nullptr;
}

void Host::Init()
{
    while (!UDP.begin(HOST_PORT))
    {
        Serial.println("UDP setup unsuccessful");
        delay(100);
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
        uint16_t nBytesRead = UDP.read((uint8_t *)&m_MsgBuffer, sizeof(UDPMessage));

        if (nBytesRead)
        {
            if (!m_MsgBuffer.ChecksumMatches())
            {
                Serial.println("checksum did not match");
            }

            if (m_MsgBuffer.clientId < clients.size())
            {
                clients[m_MsgBuffer.clientId].lastReceived = millis();
                clients[m_MsgBuffer.clientId].ip = UDP.remoteIP();
                m_LastClient = &clients[m_MsgBuffer.clientId];
            }
            else
            {
                Serial.println("Invalid id");
                m_LastClient = nullptr;
            }
            return &m_MsgBuffer;
        }
    }
    return nullptr;
}
