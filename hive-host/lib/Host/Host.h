#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <array>
#include "../../../common/defines.h"
#include "../../../common/Message.h"

struct UDPClient
{
    uint32_t lastReceived;
    uint32_t lastSent;
    IPAddress ip;

    bool IsConnected() { return (uint32_t)(millis() - lastReceived) < 255; }

    UDPClient() : lastReceived(0), lastSent(0) {}
};

class Host
{
public:
    Host();
    void Init();
    int SendMessage(UDPMessage *message, UDPClient &client);
    int RespondToClient(UDPMessage *message);
    UDPMessage *ReadMessage();

    std::array<UDPClient, MAX_CLIENTS> clients;

private:
    UDPClient *m_LastClient;
    UDPMessage m_MsgBuffer;
    WiFiUDP UDP;
};