#include "HiveClient.h"

HiveClient::HiveClient(uint8_t id)
{
    hostAddress = IPAddress(192, 168, 4, 1);
    isConnected = false;
    m_Message.clientId = id;
    m_LastReceived = 0;
    m_LastSent = 0;
    onConnectionChanged = nullptr;
}

void HiveClient::Init()
{
    fill_solid(m_Message.leds, LEDS_ARRAY_SIZE, CRGB::BlueViolet);
    // Start listening to this port for incoming messages
    while (!UDP.begin(CLIENT_PORT))
    {
        Serial.println("UDP setup unsuccessful");
        delay(250);
    }

    Serial.println("UDP setup successful");
}

UDPMessage &HiveClient::GetMessage()
{
    return m_Message;
}

UDPMessage *HiveClient::ReadMessage()
{
    uint8_t packetSize = UDP.parsePacket();

    if (packetSize)
    {
        m_LastReceived = millis();

        if (UDP.read((uint8_t *)&m_Message, sizeof(UDPMessage)))
            return &m_Message;
    }
    return nullptr;
}

bool HiveClient::IsNextFrameAvailable()
{
    return (uint32_t)(millis() - m_LastSent) > m_Message.requestNextFrameMs;
}

int HiveClient::RequestFrame()
{
    if (!IsNextFrameAvailable())
        return -1;

    return SendPing();
}

int HiveClient::SendPing()
{
    if (!isConnected)
        return -1;

    m_LastSent = millis();
    if (UDP.beginPacket(hostAddress, HOST_PORT))
    {
        UDP.write((uint8_t *)&m_Message, sizeof(UDPMessage));
        return UDP.endPacket();
    }
    return 0;
}

void HiveClient::OnConnectionChanged()
{
    if (onConnectionChanged)
        onConnectionChanged(isConnected);
}

void HiveClient::TestConnection()
{
    bool hasConnection = WiFi.status() == WL_CONNECTED;

    if (hasConnection && !isConnected)
    {
        isConnected = true;
        OnConnectionChanged();
    }

    if (!hasConnection && isConnected)
    {
        isConnected = false;
        OnConnectionChanged();
    }
}