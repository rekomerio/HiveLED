#include "HiveClient.h"

HiveClient::HiveClient(uint8_t id, IPAddress hostAddress)
{
    this->id = id;
    this->hostAddress = hostAddress;
    m_LastReceived = 0;
    m_LastSent = 0;
}

uint8_t HiveClient::Init()
{
    // Start listening to this port for incoming messages
    return UDP.begin(CLIENT_PORT);
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
    if (ElapsedSinceLastSent() < 50)
        return 0;

    return SendPing();
}

int HiveClient::SendPing()
{
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

uint32_t lastT = 0;

void HiveClient::Loop()
{
    KeepAlive();
    UDPMessage *message = ReadMessage();

    if (message)
    {
        FastLED.setBrightness(message->brightness);
        FastLED.show();
    }
}