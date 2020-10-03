#include "MessageHandler.h"

MessageHandler::MessageHandler()
{
}

void MessageHandler::Handle(UDPMessage *message)
{
    if (message->clientId > effects.size())
        return;

    LEDEffects &effect = effects[message->clientId];

    if (effect.params.syncWithId != 0xFF && effect.params.syncWithId < MAX_CLIENTS)
    {
        Synchronize(effect.params, effects[effect.params.syncWithId].params);
    }

    message->brightness = effect.params.brightness;
    message->requestNextFrameMs = effect.params.nextFrameMs;

    effect.Update(message->leds);
}

void MessageHandler::Synchronize(LEDParams &to, LEDParams &with)
{
    to.palettePosition = with.palettePosition;
    to.activeEffect = with.activeEffect;
    to.brightness = with.brightness;
}