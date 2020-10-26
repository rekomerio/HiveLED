#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "../../../common/defines.h"
#include "../../../common/Message.h"

#ifndef HIVECLIENT_H
#define HIVECLIENT_H

typedef void (*Callback)(bool isConnected);

class HiveClient
{
public:
    enum
    {
        NO_FRAME = -10,
        NO_CONNECTION,
        HOST_OVERLOAD
    };

    HiveClient(uint8_t id, IPAddress hostAddress);

    uint8_t Init();
    CRGB *GetLeds();
    UDPMessage *ReadMessage();
    int RequestFrame();
    int SendPing();
    void TestConnection();
    bool IsNextFrameAvailable();
    uint32_t ElapsedSinceLastReceived();
    uint32_t ElapsedSinceLastSent();
    int KeepAlive();
    void Loop();

    uint8_t id;
    IPAddress hostAddress;

    Callback onConnectionChanged;

private:
    void OnConnectionChanged();

    WiFiUDP UDP;
    UDPMessage m_Message;
    uint32_t m_LastReceived;
    uint32_t m_LastSent;
};

#endif