#include "HiveClient.h"

HiveClient::HiveClient(uint8_t id)
{
    hostAddress = IPAddress(192, 168, 4, 1);
    isConnected = false;
    onConnectionChanged = nullptr;
    this->id = id;
    m_LastReceived = 0;
    m_LastSent = 0;
}

void HiveClient::Init()
{
    fill_solid(GetLeds(), LEDS_ARRAY_SIZE, CRGB::BlueViolet);
    // Start listening to this port for incoming messages
    while (!UDP.begin(CLIENT_PORT))
    {
        Serial.println("UDP setup unsuccessful");
        delay(250);
    }

    Serial.println("UDP setup successful");
}

CRGB *HiveClient::GetLeds()
{
    return m_Message.leds;
}

UDPMessage *HiveClient::ReadMessage()
{
    if (UDP.parsePacket())
    {
        if (UDP.read((uint8_t *)&m_Message, sizeof(UDPMessage)))
        {
            if (m_Message.clientId == id)
            {
                m_LastReceived = millis();
                return &m_Message;
            }
        }
    }
    return nullptr;
}

bool HiveClient::IsNextFrameAvailable()
{
    return ElapsedSinceLastReceived() > m_Message.requestNextFrameMs;
}

uint32_t HiveClient::ElapsedSinceLastReceived()
{
    return (uint32_t)(millis() - m_LastReceived);
}

uint32_t HiveClient::ElapsedSinceLastSent()
{
    return (uint32_t)(millis() - m_LastSent);
}

int HiveClient::RequestFrame()
{
    if (!IsNextFrameAvailable())
        return NO_FRAME;

    return SendPing();
}

int HiveClient::KeepAlive()
{
    if (ElapsedSinceLastSent() < 100)
        return 0;

    return SendPing();
}

int HiveClient::SendPing()
{
    if (!isConnected)
        return NO_CONNECTION;

    if (ElapsedSinceLastSent() < 5)
        return HOST_OVERLOAD;

    if (UDP.beginPacket(hostAddress, HOST_PORT))
    {
        UDP.write(&id, 1);
        uint8_t isSuccess = UDP.endPacket();

        if (isSuccess)
            m_LastSent = millis();

        return isSuccess;
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

    if (hasConnection != isConnected)
    {
        isConnected = hasConnection;
        OnConnectionChanged();
    }
}