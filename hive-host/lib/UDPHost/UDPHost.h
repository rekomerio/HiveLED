#ifndef UDPHOST_H
#define UDPHOST_H

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

class UDPHost
{
public:
    UDPHost();
    void Init();
    int SendMessage(UDPMessage *message, UDPClient &client);
    int RespondToClient(UDPMessage *message);
    UDPMessage *ReadMessage();
    UDPMessage *PeekMessage();

    std::array<UDPClient, MAX_CLIENTS> clients;

private:
    uint8_t m_NextMessageIndex;
    UDPClient *m_LastClient;
    std::array<UDPMessage, MAX_CLIENTS> m_MsgBuffer;
    WiFiUDP UDP;
};

#endif