#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "../../../common/defines.h"
#include "../../../common/Message.h"

typedef void (*Callback)(bool isConnected);

class HiveClient
{
public:
    enum {
        NO_FRAME = -10,
        NO_CONNECTION,
        HOST_OVERLOAD
    };

    HiveClient(uint8_t id);

    void Init();
    UDPMessage &GetMessage();
    UDPMessage *ReadMessage();
    int RequestFrame();
    void TestConnection();
    bool IsNextFrameAvailable();
    uint32_t ElapsedSinceLastReceived();
    uint32_t ElapsedSinceLastSent();

    bool isConnected;
    uint8_t id;
    IPAddress hostAddress;

    Callback onConnectionChanged;

private:
    int SendPing();
    void OnConnectionChanged();

    WiFiUDP UDP;
    UDPMessage m_Message;
    uint32_t m_LastReceived;
    uint32_t m_LastSent;
};