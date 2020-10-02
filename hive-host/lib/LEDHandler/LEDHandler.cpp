#include "LEDHandler.h"

LEDHandler::LEDHandler()
{
}

void LEDHandler::Init()
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        clients[i].id = i;
    }
}

void LEDHandler::Handle(UDPMessage *message)
{
    if (message->clientId > clients.size())
        return;

    switch (clients[message->clientId].activeEffect)
    {
    case 0:
        Confetti(message->leds, message->clientId);
        break;
    default:
        clients[message->clientId].activeEffect = 0;
    }
}

void LEDHandler::Confetti(CRGB *leds, uint8_t clientId)
{
    if (clientId > clients.size())
        return;

    auto &client = clients[clientId];

    if (millis() - client.lastUpdate > client.spawnRate)
    {
        leds[random16(72)] += CHSV(client.hue + random8(64), 200, 255);
        client.lastUpdate = millis();
    }

    fadeToBlackBy(leds, 72, 5);
}