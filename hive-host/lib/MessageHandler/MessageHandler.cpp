#include "MessageHandler.h"

MessageHandler::MessageHandler()
{
}

void MessageHandler::Init()
{
    uint8_t i = 0;
    effects.push_back(new Confetti(i++));
    effects.push_back(new Rainbow(i++));
    effects.push_back(new Sinelon(i++));
    effects.push_back(new Bpm(i++));
    effects.push_back(new Juggle(i++));
    effects.push_back(new ColorPalette(i++));
}

void MessageHandler::Handle(UDPMessage *message)
{
    if (message->clientId > params.size())
        return;

    LEDParams &param = params[message->clientId];

    if (param.syncWithId == message->clientId)
        param.syncWithId = 255; // Cant sync with itself

    if (param.syncWithId != 0xFF && param.syncWithId < MAX_CLIENTS)
        Synchronize(param, params[param.syncWithId]);

    message->brightness = param.brightness;
    message->requestNextFrameMs = param.nextFrameMs;

    param.activeEffect %= effects.size();

    effects[param.activeEffect]->Update(message->leds, param);
}

void MessageHandler::Synchronize(LEDParams &sync, LEDParams &with)
{
    sync.palettePosition = with.palettePosition;
    sync.activeEffect = with.activeEffect;
    sync.brightness = with.brightness;
}

LEDParams *MessageHandler::GetParams(uint8_t clientId)
{
    return &params[clientId];
}